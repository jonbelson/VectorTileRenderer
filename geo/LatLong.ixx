// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module geo.latlong;

namespace geo::latlong
{
	// Latitude and longitude in decimal degrees.
	export struct LatLong
	{
		double latitude {};
		double longitude {};
	};
};
