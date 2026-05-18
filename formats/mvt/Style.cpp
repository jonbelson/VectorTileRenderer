// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include "json.hpp"

#include <fstream>

module formats.mvt.style;

import std;

import core.logger;
import formats.mvt.parser;
import io.gzip;
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
				std::string jsonUrl { spriteUrl };
				std::string pngUrl { spriteUrl };

				auto pos = spriteUrl.find_first_of('?');

				if (pos == std::string::npos)
				{
					jsonUrl.append(suffix.json);
					pngUrl.append(suffix.png);
				}
				else
				{
					jsonUrl.insert(pos, suffix.json);
					pngUrl.insert(pos, suffix.png);
				}

				auto jsonResult = io::resource::LoadFromUri(jsonUrl);
				auto pngResult = io::resource::LoadFromUri(pngUrl);

				if (jsonResult && pngResult)
				{
					io::resource::Data json = std::move(jsonResult.value());

					if (io::gzip::IsGzipped(json))
					{
						json = io::gzip::Decompress(json);
					}

					//io::resource::SaveData(json, "t:/jsonResult.json");
					//io::resource::SaveData(pngResult.value(), "t:/pngResult.png");

					const auto jsonData = nlohmann::json::parse(json.begin(), json.end(), nullptr, false);
					auto bitmap = core::bitmap::LoadBitmapFromResource(pngResult.value());

					if (bitmap && !jsonData.is_discarded())
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

						core::logger::Info("Loaded sprites from {} and {}\n", jsonUrl, pngUrl);

						return true;
					}

				}
			}

		}

		core::logger::Error("Failed to load sprites from '{}'\n", spriteUrl);

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


	static std::vector<std::string> ParseTileUrlsFromSource(const json& data)
	{
		std::vector<std::string> tileUrls;
		if (data.contains("tiles") && data.at("tiles").is_array())
		{
			for (const auto& tileUrl : data.at("tiles"))
			{
				if (tileUrl.is_string())
				{
					tileUrls.push_back(tileUrl.get<std::string>());
				}
			}
		}
		return tileUrls;
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
				for (const auto& [key, value] : n.items())
				{
					Source source;
					TryReadString(value, "type", source.mType);
					TryReadString(value, "url", source.mUrl);
					TryReadString(value, "attribution", source.mAttribution);
					TryReadString(value, "copyright", source.mCopyright);
					TryReadInt(value, "minzoom", source.mMinZoom);
					TryReadInt(value, "maxzoom", source.mMaxZoom);

					auto tileUrls = ParseTileUrlsFromSource(value);

					if (tileUrls.empty())
					{
						// If no '"tiles": []' is present, we need to fetch from 'url' and parse from the result.
						auto result = io::resource::LoadFromUri(source.mUrl);
						if (result)
						{
							const auto& data = result.value();
							json parsedJson = json::parse(data.begin(), data.end(), nullptr, false);

							tileUrls = ParseTileUrlsFromSource(parsedJson);
						}
					}

					if (!tileUrls.empty())
					{
						source.mTiles = std::move(tileUrls);
					}
					else
					{
						core::logger::Error(std::format("Failed to parse 'tiles' from Style\n"));
					}

					mSources[key] = source;
				}

				// For simplicity's sake, just copy the first tile URL. XXX Handle 'source' and use multiple tile URLs.
				if (!mSources.empty())
				{
					if (!mSources.begin()->second.mTiles.empty())
					{
						mSourceTileUrl = mSources.begin()->second.mTiles.front();
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
			core::logger::Error("Failed to load sprites from {}\n", mSpriteUrl);
		}

		mGlyphs = Glyphs(mGlyphUrl);

		return true;
	}

	std::shared_ptr<Style> Style::LoadFromFile(const std::string& fileName)
	{
		std::ifstream f(fileName.c_str());
		if (f.is_open())
		{
			const json data = json::parse(f, nullptr, false);

			std::shared_ptr<Style> style = std::make_shared<Style>();

			if (style->ParseFromJson(data))
				return style;
		}

		core::logger::Error("Failed to load style from {}\n", fileName);

		return nullptr;
	}

	std::shared_ptr<Style> Style::LoadFromString(const std::string& s)
	{
		const json data = json::parse(s, nullptr, false);

		std::shared_ptr<Style> style = std::make_shared<Style>();

		if (style->ParseFromJson(data))
			return style;

		core::logger::Error("Failed to load style from {}\n", s);

		return nullptr;
	}

	std::shared_ptr<Style> Style::LoadFromUrl(const std::string& url)
	{
		auto result = io::resource::LoadFromUri(url);
		if (result)
		{
			const auto& data = result.value();
			json parsedJson = json::parse(data.begin(), data.end(), nullptr, false);

			if (parsedJson.size() == 1 && parsedJson.contains("error"))
			{
				std::string msg = parsedJson.dump() + "\n";
				core::logger::Error(msg);

				return nullptr;
			}

			std::shared_ptr<Style> style = std::make_shared<Style>();

			if (style->ParseFromJson(parsedJson))
				return style;
		}

		core::logger::Error("Failed to load style from {}\n", url);

		return nullptr;
	}

}
