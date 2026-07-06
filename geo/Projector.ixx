module;

#include <proj.h>

export module geo.projector;

import std;
import geo.latlong;

namespace geo::projector
{
	export struct Coord
	{
		double x{};
		double y{};
	};

	//export using Coord = std::variant<geo::latlong::LatLong, Grid>;

	/*

	PJ_PROJ

	xy		Projected 2D	x, y
	xyz		Cartesian 3D	x, y, z
	xyzt	Cartesian 4D	x, y, z, t
	lp		Geographic 2D	lam, phi
	lpz		Geographic 3D	lam, phi, z
	lpzt	Geographic 4D	lam, phi, z, t
	uv		Generic 2D		u, v
	uvwt	Generic 4D		u, v, w, t

	*/

	export enum Error
	{
		Unknown
	};

	export class Projector;
	export using ProjectorPtr = std::unique_ptr<Projector>;

	export class Projector
	{
		PJ_CONTEXT* mContext{};
		PJ* mProjection{};

		PJ_TYPE mSourceType { PJ_TYPE_UNKNOWN };
		PJ_TYPE mTargetType { PJ_TYPE_UNKNOWN };

		Projector()
		{
			mContext = proj_context_create();
		}

		bool Init(const std::string& source, const std::string& target)
		{
			if (!mContext)
			{
				return false;
			}

			if (mProjection)
			{
				proj_destroy(mProjection);
				mProjection = nullptr;
			}

			mProjection = proj_create_crs_to_crs(mContext, source.c_str(), target.c_str(), nullptr);

			if (mProjection)
			{
				// Use normalized order so that horizontal comes first, then vertiical.
				PJ* normal = proj_normalize_for_visualization(mContext, mProjection);
				proj_destroy(mProjection);
				mProjection = normal;

				if (mProjection)
				{
					PJ* sourceCrs = proj_get_source_crs(mContext, mProjection);
					PJ* targetCrs = proj_get_target_crs(mContext, mProjection);

					if (sourceCrs && targetCrs)
					{
						mSourceType = proj_get_type(mProjection);
						mTargetType = proj_get_type(mProjection);
					}

					if (sourceCrs) proj_destroy(sourceCrs);
					if (targetCrs) proj_destroy(targetCrs);
				}
			}

			return mProjection != nullptr;
		}

	public:
		~Projector()
		{
			if (mProjection)
			{
				proj_destroy(mProjection);
				mProjection = nullptr;
			}
			if (mContext)
			{
				proj_context_destroy(mContext);
				mContext = nullptr;
			}
		}



		PJ_COORD Project(PJ_COORD coord)
		{
			PJ_COORD result = proj_trans(mProjection, PJ_FWD, coord);

			return result;
		}

		PJ_COORD Unproject(PJ_COORD coord)
		{
			PJ_COORD result = proj_trans(mProjection, PJ_INV, coord);

			return result;
		}

		Coord Project(const Coord& coord)
		{
			PJ_COORD pjCoord = proj_coord(coord.x, coord.y, 0.0, 0.0);
			PJ_COORD result = proj_trans(mProjection, PJ_FWD, pjCoord);

			return Coord{ result.v[0], result.v[1] };
		}

		Coord Unproject(const Coord& coord)
		{
			PJ_COORD pjCoord = proj_coord(coord.x, coord.y, 0.0, 0.0);
			PJ_COORD result = proj_trans(mProjection, PJ_INV, pjCoord);

			return Coord{ result.v[0], result.v[1] };
		}

		// source	Source CRS, e.g. "EPSG:4326" (WGS84), "EPSG:3857" (Web Mercator)
		// target	Target CRS, e.g. "EPSG:4326" (WGS84), "EPSG:3857" (Web Mercator)
		static std::expected <ProjectorPtr, Error> Create(const std::string& source, const std::string& target)
		{
			ProjectorPtr projector = std::unique_ptr<Projector>(new Projector());

			if (projector->Init(source, target))
			{
				return std::move(projector);
			}

			return std::unexpected(Error::Unknown);
		}

	};


};
