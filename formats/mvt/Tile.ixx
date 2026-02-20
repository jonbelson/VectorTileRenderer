module;

#include "vector_tile.pb.h"

#include <cstdint>
#include <atltrace.h>

export module formats.mvt.tile;

import formats.mvt.feature;


namespace mvt::tile
{

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

		//std::string mLayerName;

		//std::vector<mvt::feature::Feature> mFeatures;
	};

	export void MyFunc();

	export std::unique_ptr<Tile> DecodeTile(std::vector<std::byte>& data);

	export double GetLatitude(int zoom, int x, int y);
	export double GetLongitude(int zoom, int x, int y);
	export std::pair<double, double> TileToLatLong(int zoom, int x, int y);

	export std::pair<int, int> LatLongToTile(int zoom, double latitude, double longitude);

	export int LongToTileX(double longitudeDeg, int zoom);
	export int LatToTileY(double latitudeDeg, int zoom);

	export double TileXToLong(int x, int zoom);
	export double TileYToLat(int y, int zoom);

}
