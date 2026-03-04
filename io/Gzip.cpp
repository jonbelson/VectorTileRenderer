module;

#include <cstdint>

#include "zlib.h"

module io.gzip;

namespace io::gzip
{

	std::vector<std::byte> Decompress(std::span<std::byte> input)
	{
		std::vector<std::byte> output;

		z_stream stream{};
		stream.next_in = reinterpret_cast<uint8_t*>(input.data());
		stream.avail_in = static_cast<uInt>(input.size());

		if (inflateInit2(&stream, 16 + MAX_WBITS) == Z_OK)
		{
			output.resize(input.size()*2);

			stream.next_out = reinterpret_cast<uint8_t*>(output.data());
			stream.avail_out = static_cast<uInt>(output.size());

			while (true)
			{
				int ret = inflate(&stream, Z_NO_FLUSH);

				if (ret == Z_STREAM_END)
				{
					// Done;
					break;
				}

				if (ret != Z_OK)
				{
					output = {};
					break;
				}

				// Need more space to continue decompressing.
				size_t outputSize = output.size();

				output.resize(outputSize*2);

				stream.next_out = reinterpret_cast<uint8_t*>(output.data() + outputSize);
				stream.avail_out = static_cast<uInt>(outputSize);

			}

		}


		if (!output.empty())
		{
			output.resize(stream.total_out);
		}

		inflateEnd(&stream);

		return output;
	}

	// Return true if data begins with the gzip marker 0x1f 0x8b.
	bool IsGzipped(const std::span<std::byte> input)
	{
		if (input.size() >= 2)
		{
			if (input[0] == (std::byte) 0x1f && input[1] == (std::byte) 0x8b)
			{
				return true;
			}
		}
		return false;
	}


};
