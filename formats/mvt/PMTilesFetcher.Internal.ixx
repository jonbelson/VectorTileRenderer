// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.pmtilesfetcher.internal;

import std;

import core.json;
import core.logger;
import geo.latlong;
import io.file;
import io.gzip;

namespace mvt::tilefetcher
{
	using uint8_t = std::uint8_t;
	using uint32_t = std::uint32_t;
	using uint64_t = std::uint64_t;

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
	};




};
