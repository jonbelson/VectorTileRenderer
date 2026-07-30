// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module io.file;

import std;

namespace io::file
{
	export using Data = std::vector<std::byte>;

	export enum struct Status
	{
		Unknown, FileNotFound, FileReadError
	};

	export class FileReader;
	using FileReaderPtr = std::unique_ptr<FileReader>;

	export template<std::floating_point T, std::endian SourceEndian>
		bool Read(std::span<const std::byte> bytes, T& val)
	{
		if (bytes.size() != sizeof(T)) return false;

		using TempType = std::conditional<sizeof(T) == 4, std::uint32_t, std::uint64_t>::type;

		TempType temp{};

		std::memcpy(&temp, bytes.data(), sizeof(T));

		if constexpr (std::endian::native != SourceEndian)
		{
			temp = std::byteswap(temp);
		}

		val = std::bit_cast<T, TempType>(temp);

		return true;
	}

	export template<std::integral T, std::endian SourceEndian>
		bool Read(std::span<const std::byte> bytes, T& val)
	{
		if (bytes.size() != sizeof(T)) return false;

		std::memcpy(&val, bytes.data(), sizeof(T));

		if constexpr (std::endian::native != SourceEndian)
		{
			val = std::byteswap(val);
		}

		return true;
	}

	export template<typename T>
		bool ReadLE(std::span<const std::byte> bytes, T& val)
	{
		return Read<T, std::endian::little>(bytes, val);
	}

	export template<typename T>
		bool ReadBE(std::span<const std::byte> bytes, T& val)
	{
		return Read<T, std::endian::big>(bytes, val);
	}

	export bool Read(std::span<std::byte> bytes, std::string& s)
	{
		s.resize(bytes.size());

		std::memcpy(s.data(), bytes.data(), bytes.size());

		return true;
	}


	export class FileReader
	{
		std::ifstream mFile;

		size_t mFileSize{};

		FileReader()
		{
		}

		bool Open(std::string_view sv)
		{
			mFile.open(std::string(sv).c_str(), std::ios::binary);

			if (!mFile.is_open()) return false;

			mFile.seekg(0, std::ios::end);

			auto fileSize = mFile.tellg();
			mFileSize = static_cast<size_t>(fileSize);

			mFile.seekg(0, std::ios::beg);

			return true;
		}

	public:

		Data Read(size_t start, size_t size)
		{
			if (!mFile) return {};
			if (start > mFileSize) return {};

			mFile.seekg(static_cast<std::streampos>(start));

			size_t bytesToRead = size;
			if (start + bytesToRead > mFileSize)
			{
				bytesToRead = mFileSize - start;
			}

			Data data(bytesToRead);

			mFile.read(reinterpret_cast<char*>(&data[0]), static_cast<std::streamsize>(bytesToRead));

			data.resize(mFile.gcount());

			return data;
		}

		static std::expected<FileReaderPtr, Status> Create(std::string_view sv)
		{
			std::error_code ec {};
			bool exists = std::filesystem::is_regular_file(sv, ec);

			if (!exists) return std::unexpected(Status::FileNotFound);

			FileReaderPtr fileReader = std::unique_ptr<FileReader>(new FileReader());

			if (fileReader->Open(sv))
			{
				return fileReader;
			}

			return std::unexpected(Status::FileReadError);
		}

	};


}
