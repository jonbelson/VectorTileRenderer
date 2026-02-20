module;

#include "curl/curl.h"

module io.resource;

namespace io::resource
{


	std::expected<Data, Status> LoadFromFile(std::string_view sv)
	{
		std::ifstream f(std::string(sv).c_str(), std::ios::binary);
		if (f.is_open())
		{
			f.seekg(0, std::ios::end);
			std::streamsize size = f.tellg();

			f.seekg(0, std::ios::beg);

			std::vector<std::byte> buffer(size);
			if (f.read((char*)buffer.data(), size))
			{
				return buffer;
			}
			else
			{
				return std::unexpected(Status::FileReadError);
			}
		}
		else
		{
			return std::unexpected(Status::FileNotFound);
		}

		return std::unexpected(Status::Unknown);
	}

	struct MemoryStruct
	{
		//char* memory{};
		Data data;
		//size_t size{};
	};

	size_t CurlCallback(void* contents, size_t size, size_t nmemb, void* userData)
	{
		//MemoryStruct* memoryStruct = reinterpret_cast<struct MemoryStruct*>(userData);

		Data* data = reinterpret_cast<Data*>(userData);

		size_t blockSize = size*nmemb;

		//if (blockSize > memoryStruct->data.size())
		{
			size_t currSize = data->size();
			data->resize(currSize + blockSize /*+ 1*/);
			std::memcpy(data->data() + currSize, contents, blockSize);

			//data->back() = (std::byte)0;
		}

		return blockSize;
	}

	std::expected<Data, Status> LoadFromHttp(std::string_view url)
	{
		CURL* curlHandle{};

		//struct MemoryStruct chunk;
		Data chunk;

		//chunk.memory = (char*) malloc(1);
		//chunk.size = 0;

		curl_global_init(CURL_GLOBAL_ALL);

		curlHandle = curl_easy_init();

		curl_easy_setopt(curlHandle, CURLOPT_URL, std::string(url).c_str());

		curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, CurlCallback);

		curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*) &chunk);

		curl_easy_setopt(curlHandle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

		CURLcode result = curl_easy_perform(curlHandle);

		if (result != CURLE_OK)
		{
			curl_easy_cleanup(curlHandle);

			//free(chunk.memory);

			curl_global_cleanup();

			return std::unexpected(Status::HttpError);
		}

		curl_easy_cleanup(curlHandle);

		//free(chunk.memory);

		curl_global_cleanup();

		return chunk;

		//return std::unexpected(Status::Unknown);
	}

	// Attempt to call the appropriate Load*() function based on prefix.
	std::expected<Data, Status> LoadFromUri(std::string_view uri)
	{
		if (uri.starts_with("file://"))
		{
			return LoadFromFile(uri.substr(7, uri.length() - 7));
		}
		else if (uri.starts_with("http://") || uri.starts_with("https://"))
		{
			return LoadFromHttp(uri);
		}

		return std::unexpected(Status::InvalidUri);
	}



	bool SaveData(const Data& data, const std::string& fileName)
	{
		std::ofstream f(fileName.c_str(), std::ios::binary);
		if (f.is_open())
		{
			f.write((char*)data.data(), data.size());

			return !f;
		}

		return false;
	}




};
