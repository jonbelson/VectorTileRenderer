// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.pmtilesfetcher.internal;

import std;

import core.json;
import core.logger;
import formats.mvt.tile;
import geo.latlong;
import io.file;
import io.gzip;

namespace mvt::tilefetcher
{
	using uint8_t = std::uint8_t;
	using uint32_t = std::uint32_t;
	using uint64_t = std::uint64_t;

	using TileSpec = mvt::tile::TileSpec;

	export size_t CountForZoom(uint64_t zoom)
	{
		size_t n = 1ULL<<zoom;
		size_t count = n*n;
		return count;
	}

	export size_t BaseForZoom(uint64_t zoom)
	{
		size_t total{};
		for (uint64_t i = 0; i<zoom; i++)
		{
			total += CountForZoom(i);
		}
		return total;
	}

	export uint64_t ZoomForTileID(uint64_t TileID)
	{
		if (TileID == 0) return 0;

		uint64_t zoom{};
		uint64_t base{};

		while ((zoom<<2) + base <= TileID)
		{
			base += CountForZoom(zoom);
			zoom++;
		}

		return zoom;
	}

	/*
	template<size_t N>
	using Indices = std::make_index_sequence<N>;

	template<size_t... Is>
	constexpr size_t TotalForZoom(std::index_sequence<Is...>)
	{
		return (CountForZoom<Is>() + ...);
	}

	constexpr size_t Count1 = TotalForZoom(Indices<1>{});
	constexpr size_t Count2 = TotalForZoom(Indices<2>{});
	constexpr size_t Count3 = TotalForZoom(Indices<3>{});
	*/

	static void Rotate(uint64_t s, uint64_t rx, uint64_t ry, uint64_t& x, uint64_t& y)
	{
		if (ry == 0)
		{
			if (rx == 1)
			{
				x = s*s - 1 - x;
				y = s*s - 1 - y;
			}
			std::swap(x, y);
		}
	}

	export TileSpec TileIDToTileSpec(uint64_t TileID)
	{
		uint64_t zoom = ZoomForTileID(TileID);

		uint64_t n = 1ULL << zoom;

		uint64_t base = BaseForZoom(zoom);
		uint64_t d = TileID - base;

		uint64_t x{};
		uint64_t y{};
		uint64_t t{ d };

		uint64_t s{ 1 };

		while (s < n)
		{
			uint64_t rx = 1 & (t/2);
			uint64_t ry = 1 & (t xor rx);

			Rotate(s, rx, ry, x, y);

			x += s*rx;
			y += s*ry;

			t /= 4;

			s<<= 1;
		}

		return TileSpec{ .zoom = static_cast<int>(zoom), .y = static_cast<int>(y), .x = static_cast<int>(x) };
	}

	export uint64_t TileSpecToTileID(const TileSpec& tileSpec)
	{
		uint64_t zoom = static_cast<uint64_t>(tileSpec.zoom);
		uint64_t y = static_cast<uint64_t>(tileSpec.y);
		uint64_t x = static_cast<uint64_t>(tileSpec.x);

		size_t base = (zoom) ? BaseForZoom(zoom) : 0;

		uint64_t d{};

		int n = 1<<zoom;
		uint64_t s = n/2;

		while (s)
		{
			uint64_t rx = (x & s) ? 1 : 0;
			uint64_t ry = (y & s) ? 1 : 0;

			d += s*s*((3*rx) xor ry);

			Rotate(s, rx, ry, x, y);

			s /= 2;
		}

		return base + d;
	}

	export enum struct Compression
	{
		Unknown, None, Gzip, Brotli, Zstd
	};

	export enum struct TileType
	{
		Unknown, Mvt, Png, Jpeg, WebP, Avif, MapLibre
	};

	Compression ValueToCompression(uint8_t compression)
	{
		switch (compression)
		{
			case 0: return Compression::Unknown;
			case 1: return Compression::None;
			case 2: return Compression::Gzip;
			case 3: return Compression::Brotli;
			case 4: return Compression::Zstd;

			default: return Compression::Unknown;
		}
	}

	TileType ValueToTileType(uint8_t tileType)
	{
		switch (tileType)
		{
			case 0: return TileType::Unknown;
			case 1: return TileType::Mvt;
			case 2: return TileType::Png;
			case 3: return TileType::Jpeg;
			case 4: return TileType::WebP;
			case 5: return TileType::Avif;
			case 6: return TileType::MapLibre;

			default: return TileType::Unknown;
		}
	}

	geo::latlong::LatLong ValueToLatLong(uint64_t position)
	{
		std::int32_t longitude = static_cast<int32_t>(position>>32);
		std::int32_t latitude = static_cast<int32_t>(position&0xffffffff);

		return geo::latlong::LatLong(longitude/10'000'000.0, latitude/10'000'000.0);
	}

	export struct PmTilesHeader
	{
		uint64_t RootOffset{};
		uint64_t RootLength{};
		uint64_t MetadataOffset{};
		uint64_t MetadataLength{};
		uint64_t LeafOffset{};
		uint64_t LeafLength{};
		uint64_t TileOffset{};
		uint64_t TileLength{};
		uint64_t NumAddressedTiles{};
		uint64_t NumTileEntries{};
		uint64_t NumTileContents{};
		uint8_t Clustered{};
		Compression InternalCompression{};
		Compression TileCompression{};
		TileType TileType{};
		uint8_t MinZoom{};
		uint8_t MaxZoom{};
		geo::latlong::LatLong MinPosition{};
		geo::latlong::LatLong MaxPosition{};
		uint8_t CenterZoom{};
		geo::latlong::LatLong CenterPosition{};
	};

	export struct PmTilesMetadata
	{
		std::unordered_map<std::string, std::string> Metadata;
	};

	export struct PmTilesDirectory
	{
		std::vector<uint64_t> TileIDs;
		std::vector<uint64_t> RunLengths;
		std::vector<uint64_t> Lengths;
		std::vector<uint64_t> Offsets;
	};

	export struct PmTiles
	{
		PmTilesHeader mHeader;
		PmTilesMetadata mMetadata;
		PmTilesDirectory mDirectory;

		bool ParseHeader(io::file::FileReader& fileReader)
		{
			auto data = fileReader.Read(0, 127);
			if (data.size() != 127) return false;

			io::file::DataParser dataParser(data);

			std::string s;
			bool ok = dataParser.Read(s, 7);
			if (!ok || s != "PMTiles") return false;

			uint8_t version{};
			if (ok) ok = dataParser.ReadLE(version);
			if (ok) ok = dataParser.ReadLE(mHeader.RootOffset);
			if (ok) ok = dataParser.ReadLE(mHeader.RootLength);
			if (ok) ok = dataParser.ReadLE(mHeader.MetadataOffset);
			if (ok) ok = dataParser.ReadLE(mHeader.MetadataLength);

			if (ok) ok = dataParser.ReadLE(mHeader.LeafOffset);
			if (ok) ok = dataParser.ReadLE(mHeader.LeafLength);

			if (ok) ok = dataParser.ReadLE(mHeader.TileOffset);
			if (ok) ok = dataParser.ReadLE(mHeader.TileLength);

			if (ok) ok = dataParser.ReadLE(mHeader.NumAddressedTiles);
			if (ok) ok = dataParser.ReadLE(mHeader.NumTileEntries);
			if (ok) ok = dataParser.ReadLE(mHeader.NumTileContents);

			if (ok) ok = dataParser.ReadLE(mHeader.Clustered);

			uint8_t uint8{};
			if (ok) ok = dataParser.ReadLE(uint8);
			if (ok) mHeader.InternalCompression = ValueToCompression(uint8);

			if (ok) ok = dataParser.ReadLE(uint8);
			if (ok) mHeader.TileCompression = ValueToCompression(uint8);

			if (ok) ok = dataParser.ReadLE(uint8);
			if (ok) mHeader.TileType = ValueToTileType(uint8);

			if (ok) ok = dataParser.ReadLE(mHeader.MinZoom);
			if (ok) ok = dataParser.ReadLE(mHeader.MaxZoom);

			uint64_t uint64{};
			if (ok) ok = dataParser.ReadLE(uint64);
			if (ok) mHeader.MinPosition = ValueToLatLong(uint64);
			if (ok) ok = dataParser.ReadLE(uint64);
			if (ok) mHeader.MaxPosition = ValueToLatLong(uint64);

			if (ok) ok = dataParser.ReadLE(mHeader.CenterZoom);

			if (ok) ok = dataParser.ReadLE(uint64);
			if (ok) mHeader.CenterPosition = ValueToLatLong(uint64);

			return ok;
		}

		bool ParseMetadata(io::file::FileReader& fileReader)
		{
			if (mHeader.MetadataOffset == 0 || mHeader.MetadataLength == 0) return true;

			auto data = fileReader.Read(mHeader.MetadataOffset, mHeader.MetadataLength);
			if (data.empty()) return false;

			if (io::gzip::IsGzipped(data))
			{
				data = io::gzip::Decompress(data);
			}

			using namespace core::json;

			const auto parsedJson = json::parse(data.begin(), data.end(), nullptr, false);
			if (parsedJson.is_discarded()) return false;

			

			// https://github.com/protomaps/PMTiles/blob/main/spec/v3/spec.md#5-json-metadata
			// https://github.com/mapbox/tilejson-spec/blob/22f5f91e643e8980ef2656674bef84c2869fbe76/3.0.0/README.md#33-vector_layers

			return true;
		}

		bool ParseDirectory(io::file::FileReader& fileReader)
		{
			if (mHeader.RootOffset == 0 || mHeader.RootLength == 0) return true;

			auto data = fileReader.Read(mHeader.RootOffset, mHeader.RootLength);
			if (data.empty()) return false;

			if (io::gzip::IsGzipped(data))
			{
				data = io::gzip::Decompress(data);
			}

			io::file::DataParser dataParser(data);

			uint64_t numEntries{};
			if (!dataParser.ReadVarIntLE(numEntries)) return false;

			mDirectory.TileIDs.resize(numEntries);
			mDirectory.RunLengths.resize(numEntries);
			mDirectory.Lengths.resize(numEntries);
			mDirectory.Offsets.resize(numEntries);

			uint64_t val{};
			uint64_t lastId{};
			for (uint64_t i = 0; i < numEntries; i++)
			{
				if (!dataParser.ReadVarIntLE(val)) return false;
				lastId += val;
				mDirectory.TileIDs[i] = lastId;
			}

			for (uint64_t i = 0; i < numEntries; i++)
			{
				if (!dataParser.ReadVarIntLE(val)) return false;
				mDirectory.RunLengths[i] = val;
			}

			for (uint64_t i = 0; i < numEntries; i++)
			{
				if (!dataParser.ReadVarIntLE(val)) return false;
				mDirectory.Lengths[i] = val;
			}

			for (uint64_t i = 0; i < numEntries; i++)
			{
				if (!dataParser.ReadVarIntLE(val)) return false;
				if (val == 0 && i > 0)
				{
					uint64_t prev = mDirectory.Offsets[i - 1];
					mDirectory.Offsets[i] = mDirectory.Offsets[i - 1] + mDirectory.Lengths[i - 1];
				}
				else
				{
					mDirectory.Offsets[i] = val - 1;
				}
			}

			return true;
		}

		bool Parse(io::file::FileReader& fileReader)
		{
			if (!ParseHeader(fileReader))
			{
				core::logger::Warning("Failed to parse PMTiles header\n");
				return false;
			}

			if (!ParseMetadata(fileReader))
			{
				core::logger::Warning("Failed to parse PMTiles metadata\n");
				return false;
			}

			if (!ParseDirectory(fileReader))
			{
				core::logger::Warning("Failed to parse PMTiles directory\n");
				return false;
			}


			return true;
		}

		std::vector<std::byte> FetchTile(io::file::FileReader& fileReader, uint64_t TileID)
		{
			auto it = std::ranges::lower_bound(mDirectory.TileIDs, TileID);

			if (it == mDirectory.TileIDs.end() || *it != TileID) return {};

			auto index = it - mDirectory.TileIDs.begin();

			uint64_t runLength = mDirectory.RunLengths[index];
			uint64_t length = mDirectory.Lengths[index];
			uint64_t offset = mDirectory.Offsets[index];

			auto data = fileReader.Read(mHeader.TileOffset + offset, length);

			if (io::gzip::IsGzipped(data))
			{
				data = io::gzip::Decompress(data);
			}
			
			return data;
		}
	};




};
