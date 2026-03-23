module;

#pragma warning(push)
#pragma warning(disable : 4018 4244 4251 4267)
#include "vector_tile.pb.h"
#pragma warning(pop)

#include <cstdint>
#include <atltrace.h>

export module formats.mvt.tile;

import formats.mvt.feature;
import geo.latlong;

namespace mvt::tile
{
	export struct TileSpec
	{
		int zoom {};
		int y{};
		int x{};
	};


	// https://github.com/mapbox/vector-tile-spec
	export class Tile
	{
		int mX{};
		int mY{};
		int mZoom{};

	public:
		Tile(int zoom, int x, int y) : mX(x), mY(y), mZoom(zoom) {}

		int X(void) const {
			return mX;
		}
		int Y(void) const {
			return mY;
		}
		int Zoom(void) const {
			return mZoom;
		}

		using FeatureList = std::vector<mvt::feature::Feature>;

		// Map of Tile layer name to Feature list.
		std::map<std::string, FeatureList> mFeatures;
	};

	export std::unique_ptr<Tile> DecodeTile(const tile::TileSpec& tileSpec, std::vector<std::byte>& data);

	export double GetLatitude(int zoom, int x, int y);
	export double GetLongitude(int zoom, int x, int y);
//	export std::pair<double, double> TileToLatLong(int zoom, int x, int y);
	export geo::latlong::LatLong TileToLatLong(int zoom, int x, int y);

	export std::pair<int, int> LatLongToTile(int zoom, double latitude, double longitude);
	export std::pair<int, int> LatLongToTile(int zoom, const geo::latlong::LatLong& latLong);

	export using TileSpecArray = std::vector<mvt::tile::TileSpec>;

	TileSpecArray GetTileArray(int zoom, geo::latlong::LatLong& bl, geo::latlong::LatLong& tr);

	export int LongToTileX(double longitudeDeg, int zoom);
	export int LatToTileY(double latitudeDeg, int zoom);

	export double TileXToLong(int x, int zoom);
	export double TileYToLat(int y, int zoom);

}
