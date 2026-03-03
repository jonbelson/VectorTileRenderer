module;

#include "json.hpp"

#include <atltrace.h>
#include <fstream>

module formats.mvt.style;

import std;

import formats.mvt.parser;
import io.resource;

using json = nlohmann::json;

using namespace mvt::layer;


namespace mvt::style
{

	bool Sprites::Load(const std::string& spriteUrl)
	{
		if (!spriteUrl.empty())
		{
			struct JsonAndPng
			{
				std::string json;
				std::string png;
				float scaler{1.0f};
			};

			std::vector<JsonAndPng> suffixes
			{
				{ "@3x.json", "@3x.png", 3.0f },
				{ "@2x.json", "@2x.png", 2.0f },
				{ ".json", ".png", 1.0f },

				{"/sprites@3x.json", "/sprites@3x.png", 3.0f},
				{"/sprites@2x.json", "/sprites@2x.png", 2.0f},
				{"/sprites.json", "/sprites.png", 1.0f},
			};

			for (const auto& suffix : suffixes)
			{
				std::string jsonUrl = spriteUrl + suffix.json;	// "/sprites@2x.json";
				std::string pngUrl = spriteUrl + suffix.png;	// "/sprites@2x.png";

				auto jsonResult = io::resource::LoadFromUri(jsonUrl);
				auto pngResult = io::resource::LoadFromUri(pngUrl);

				if (jsonResult && pngResult)
				{
					//io::resource::SaveData(jsonResult.value(), "t:/jsonResult.json");
					//io::resource::SaveData(pngResult.value(), "t:/pngResult.png");

					const auto jsonData = nlohmann::json::parse(jsonResult.value().begin(), jsonResult.value().end(), nullptr, false);
					auto bitmap = core::bitmap::LoadBitmapFromResource(pngResult.value());

					if (bitmap && jsonData != json::value_t::discarded)
					{
						for (const auto& [key, value] : jsonData.items())
						{
							SpriteSpec spec{.identifer = key};

							TryReadInt(value, "height", spec.height);
							TryReadInt(value, "width", spec.width);
							TryReadInt(value, "x", spec.x);
							TryReadInt(value, "y", spec.y);

							spec.rect = core::geometry::Rect(static_cast<float>(spec.x), static_cast<float>(spec.y), static_cast<float>(spec.width), static_cast<float>(spec.height) );

							mSpriteMap[key] = spec;
						}

						if (bitmap)
						{
			//				mSprites = std::shared_ptr<core::bitmap::Bitmap>(std::move(bitmap.value()));
							mSprites = std::make_shared<core::bitmap::Bitmap>(std::move(bitmap.value()));
						}

						mScaler = suffix.scaler;

						return true;
					}

				}
			}

		}

		return false;
	}

	std::optional<const SpriteSpec*> Sprites::Lookup(const std::string& identifier) const
	{
		auto it = mSpriteMap.find(identifier);
		if (it != mSpriteMap.end())
		{
			return { &(it->second) };
		}

		return {};
	}



	bool Style::ParseFromJson(const nlohmann::json& data)
	{
		TryReadInt(data, "version", mVersion);

		TryReadString(data, "sprite", mSpriteUrl);
		TryReadString(data, "glyphs", mGlyphUrl);

		if (data.contains("sources"))
		{
			if (const auto& n = data["sources"]; n.is_object())
			{
				if (n.contains("esri"))
				{
					if (const auto& n2 = n["esri"]; n2.is_object())
					{
						std::string sourceType;
						if (TryReadString(n2, "type", sourceType))
						{
							mSourceType = SourceTypeToEnum(sourceType);
						}
						TryReadString(n2, "url", mSourceTileUrl);
					}
				}
			}
		}

		if (data.contains("layers") && data["layers"].is_array())
		{
			for (const auto& jlayer : data["layers"])
			{
				auto layer = std::make_shared<layer::Layer>();

				if (layer->ParseFromJson(jlayer))
				{
					mLayers.push_back(layer);

					if (layer->mType == LayerType::Background)
					{
						mBackground.push_back(layer);
					}
					else
					{
						mSourceMap[layer->mSourceLayer].push_back(layer);
					}

				}

			}
		}

		if (!mSprites.Load(mSpriteUrl))
		{
			ATLTRACE("Failed to load sprites\n");
		}

		mGlyphs = Glyphs(mGlyphUrl);

		return true;
	}

	std::shared_ptr<Style> Style::LoadFromFile(const std::string& fileName)
	{
		std::ifstream f(fileName.c_str());
		if (f.is_open())
		{
			const json data = json::parse(f /*"{ \"array\": [ 1, 2, 3] }"*/);

			std::shared_ptr<Style> style = std::make_shared<Style>();

			if (style->ParseFromJson(data))
				return style;
		}

		return nullptr;
	}

	std::shared_ptr<Style> Style::LoadFromString(const std::string& s)
	{
		const json data = json::parse(s);

		std::shared_ptr<Style> style = std::make_shared<Style>();

		if (style->ParseFromJson(data))
			return style;

		return nullptr;
	}


	std::shared_ptr<Style> Style::LoadFromUrl(const std::string& Url)
	{
		return nullptr;
	}

}
