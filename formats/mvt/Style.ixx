module;

#include "json.hpp"

#include <fstream>

export module formats.mvt.style;

export import :glyphs;

import std;
import core.bitmap;
import core.geometry;
import core.rendertarget;
import formats.mvt.feature;
import formats.mvt.layer;
//import formats.mvt.tile;

import io.resource;


using namespace mvt;

namespace mvt::style
{
	export enum struct SourceType
	{
		Unknown,
		Vector,
		Raster,
		RasterArray,
		//RasterDem,
		GeoJson,
		Image,
		Video,
		Model
	};

	enum SourceType SourceTypeToEnum(const std::string& sourceType)
	{
		if (sourceType == "vector") return SourceType::Vector;
		if (sourceType == "raster") return SourceType::Raster;
		if (sourceType == "raster-array") return SourceType::RasterArray;
		//if (sourceType == "raster-dem") return SourceType::RasterDem;
		if (sourceType == "geojson") return SourceType::GeoJson;
		if (sourceType == "image") return SourceType::Image;
		if (sourceType == "video") return SourceType::Video;
		if (sourceType == "model") return SourceType::Model;

		return SourceType::Unknown;
	};


	// https://docs.mapbox.com/style-spec/reference/sprite/
	export struct SpriteSpec
	{
		std::string identifer;
		int height{};
		int width{};
		int x{};
		int y{};

		core::geometry::Rect rect;

		float pixelRatio{1.0f};	// https://www.datacadamia.com/web/css/pixel_ratio
		int content[4] {};

		struct FromTo { int fromTo[2]{}; };
		std::vector<FromTo> stretchX;
		std::vector<FromTo> stretchY;
	};


	export using SpriteMap = std::map<std::string, SpriteSpec>;

	// Interface to Sprites referenced by the style.
	export class Sprites
	{
		std::shared_ptr<core::bitmap::Bitmap> mSprites;

		SpriteMap mSpriteMap;

		float mScaler{ 1.0f };	// As required for 1x, 2x and 3x

	public:
		Sprites() {}

		std::shared_ptr<core::bitmap::Bitmap> GetBitmap(void) const { return mSprites; }

		bool Load(const std::string& spriteUrl);

		float GetScaler(void) const { return mScaler; }

		std::optional<const SpriteSpec*> Lookup(const std::string& identifier) const;
	};


	export struct Source
	{
		std::string mType;

		std::string mUrl;
		std::string mAttribution;
		std::string mCopyright;

		std::vector<std::string> mTiles;

		int mMinZoom{};
		int mMaxZoom {};
	};


	// OS Data Hub
	// Styles:
	// https://api.os.uk/maps/vector/v1/vts/resources/styles?srs=3857&key=bCj3UGjYGGyJzX9bQY9TssviLhFpuAtS
	//
	// Tiles:
	// https://api.os.uk/maps/vector/v1/vts/tile/{z}/{y}/{x}.pbf?key=bCj3UGjYGGyJzX9bQY9TssviLhFpuAtS&srs=3857
	//
	export class Style
	{
		/*std::shared_ptr<Style>*/ bool ParseFromJson(const nlohmann::json& data);

	public:
		static std::shared_ptr<Style> LoadFromFile(const std::string& fileName);
		static std::shared_ptr<Style> LoadFromUrl(const std::string& url);
		static std::shared_ptr<Style> LoadFromString(const std::string& s);

		std::string mName;
		std::string mPath;

		int mVersion;
		std::string mSpriteUrl;
		std::string mGlyphUrl;

		std::unordered_map<std::string, Source> mSources;

		SourceType mSourceType;		// XXX Only 'vector' supported.
		std::string mSourceTileUrl;

		Sprites mSprites;
		Glyphs mGlyphs;

		using LayerPtr = std::shared_ptr<layer::Layer>;
		std::vector<LayerPtr> mLayers;
		std::vector<LayerPtr> mBackground;

		std::map<std::string, std::vector<LayerPtr> > mSourceMap;

	};

}
