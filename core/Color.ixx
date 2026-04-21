module;

#include <cassert>
#include <cstdint>
#include <cstdio>

export module core.color;

import std;



namespace core::color
{
	export class Color;

	std::optional<Color> ParseHashRrggbb(std::string_view s);
	std::optional<Color> ParseHashRgb(std::string_view s);
	std::optional<Color> ParseRgba(std::string_view s);
	std::optional<Color> ParseHsla(std::string_view s);
	std::optional<Color> ParseHsl(std::string_view s);
	std::optional<Color> ParseCss(std::string_view s);


	export class Color
	{
	public:
		float Red = -1;
		float Green = -1;
		float Blue = -1;
		float Alpha = 1.0f;

		Color() = default;
		Color(float r, float g, float b) : Red(r), Green(g), Blue(b) {}
		Color(std::string_view s)
		{
			Color c = FromString(s);

			*this = c;

			///assert(IsValid());
		}

		static Color FromString(std::string_view s)
		{
			if (auto c = ParseHashRrggbb(s); c.has_value()) return c.value();
			if (auto c = ParseHashRgb(s); c.has_value()) return c.value();
			if (auto c = ParseRgba(s); c.has_value()) return c.value();
			if (auto c = ParseHsla(s); c.has_value()) return c.value();
			if (auto c = ParseHsl(s); c.has_value()) return c.value();
			if (auto c = ParseCss(s); c.has_value()) return c.value();

			return {};
		}

		bool operator==(const Color& other) const
		{
			return (Red == other.Red) && (Green == other.Green) && (Blue == other.Blue);
		}

		void operator*(float scale)
		{
			Red = Red*scale;
			Green = Green*scale;
			Blue = Blue*scale;
			Alpha = Alpha*scale;
		}

		bool IsValid(void) const { return Red != -1 && Green != -1 && Blue != -1; }

		static Color Lerp(const Color& c1, const Color& c2, float t)
		{
			Color c;
			if (c1.IsValid() && c2.IsValid())
			{
				c.Red = std::lerp(c1.Red, c2.Red, t);
				c.Green = std::lerp(c1.Green, c2.Green, t);
				c.Blue = std::lerp(c1.Blue, c2.Blue, t);
				c.Alpha = std::lerp(c1.Alpha, c2.Alpha, t);
			}

			return c;
		}
	};




	static std::optional<int> ParseComponent(std::string_view sv)
	{
		int result{};
		auto [ptr, ec] = std::from_chars(&sv[0], &sv[0] + 2, result, 16);
		if (ec == std::errc{})
		{
			return result;
		}
		return false;
	}

	// #RRGGBB
	std::optional<Color> ParseHashRrggbb(std::string_view s)
	{
		if (s.length() == 7 && s[0] == '#')
		{
			auto r = ParseComponent(std::string_view(&s[1], 2));
			auto g = ParseComponent(std::string_view(&s[3], 2));
			auto b = ParseComponent(std::string_view(&s[5], 2));

			if (r.has_value() && g.has_value() && b.has_value())
			{
				Color c;
				c.Red = r.value() / 255.0f;
				c.Green = g.value() / 255.0f;
				c.Blue = b.value() / 255.0f;

				return c;
			}
		}

		return {};
	}

	// #RGB
	std::optional<Color> ParseHashRgb(std::string_view s)
	{
		if (s.length() == 4 && s[0] == '#')
		{
			auto r = ParseComponent(std::string_view(&s[1], 2));
			auto g = ParseComponent(std::string_view(&s[3], 2));
			auto b = ParseComponent(std::string_view(&s[5], 2));

			if (r.has_value() && g.has_value() && b.has_value())
			{
				Color c;
				c.Red = r.value() / 15.0f;
				c.Green = g.value() / 15.0f;
				c.Blue = b.value() / 15.0f;

				return c;
			}
		}

		return {};
	}

	std::optional<Color> ParseRgba(std::string_view s)
	{
		if (s.size() > 4 && s.find("rgba(") != std::string::npos)
		{
			int r{}, g{}, b{};
			float a{};
			if (sscanf_s(s.data(), "rgba(%d,%d,%d,%f)", &r, &g, &b, &a) == 4)
			{
				Color c;
				c.Red = r / 255.0f;
				c.Green = g / 255.0f;
				c.Blue = b / 255.0f;
				c.Alpha = a;

				return c;
			}
		}

		return {};
	}

	// https://www.w3.org/TR/css-color-3/#hsl-color
	static Color HslToRgb(int hue, float sat, float light)
	{
		hue = hue % 360;

		if (hue < 0) {
			hue += 360;
		}

		sat /= 100;
		light /= 100;

		auto f = [&](int n) {
			float k = static_cast<float>((n + hue/30) % 12);
			float a = sat * std::min(light, 1 - light);
			return light - a * std::max(-1.0f, std::min({ k - 3, 9 - k, 1.0f}) );
			};

		return Color(f(0), f(8), f(4));
	}

	std::optional<Color> ParseHsla(std::string_view s)
	{
		if (s.size() > 5 && s.find("hsla(") != std::string::npos)
		{
			int hue{}, saturation{}, lightness{};
			float a{};

			if (sscanf_s(s.data(), "hsla(%d,%d%%,%d%%,%f)", &hue, &saturation, &lightness, &a) == 4)
			{
				Color c = HslToRgb(hue, static_cast<float>(saturation), static_cast<float>(lightness));
				c.Alpha = a;
				return c;
			}

		}

		return {};
	}

	std::optional<Color> ParseHsl(std::string_view s)
	{
		if (s.size() > 4 && s.find("hsl(") != std::string::npos)
		{
			int hue{}, saturation{}, lightness{};

			if (sscanf_s(s.data(), "hsl(%d,%d%%,%d%%)", &hue, &saturation, &lightness) == 3)
			{
				Color c = HslToRgb(hue, static_cast<float>(saturation), static_cast<float>(lightness));
				return c;
			}

		}

		return {};
	}

	// https://www.w3.org/TR/css-color-3/#svg-color
	static std::unordered_map<std::string_view /*name*/, std::pair<std::string_view /*hashRgb*/, std::string_view /*rgb*/> > cssColours =
	{
		{	"aliceblue",		{ "#f0f8ff", "rgb(240,248,255)" }	},
		{	"antiquewhite",		{ "#faebd7", "rgb(250,235,215)" }	},
		{	"aqua",				{ "#00ffff", "rgb(0,255,255)" }		},
		{	"aquamarine",		{ "#7fffd4", "rgb(127,255,212)" }	},
		{	"azure",			{ "#f0ffff", "rgb(240,255,255)" }	},
		{	"beige",			{ "#f5f5dc", "rgb(245,245,220)" }	},
		{	"bisque",			{ "#ffe4c4", "rgb(255,228,196)" }	},
		{	"black",			{ "#000000", "rgb(0,0,0)" }			},
		{	"blanchedalmond",	{ "#ffebcd", "rgb(255,235,205)" }	},
		{	"blue",				{ "#0000ff", "rgb(0,0,255)" }		},
		{	"blueviolet",		{ "#8a2be2", "rgb(138,43,226)" }	},
		{	"brown",			{ "#a52a2a", "rgb(165,42,42)" }		},
		{	"burlywood",		{ "#deb887", "rgb(222,184,135)" }	},
		{	"cadetblue",		{ "#5f9ea0", "rgb(95,158,160)" }	},
		{	"chartreuse",		{ "#7fff00", "rgb(127,255,0)" }		},
		{	"chocolate",		{ "#d2691e", "rgb(210,105,30)" }	},
		{	"coral",			{ "#ff7f50", "rgb(255,127,80)" }	},
		{	"cornflowerblue",	{ "#6495ed", "rgb(100,149,237)" }	},
		{	"cornsilk",			{ "#fff8dc", "rgb(255,248,220)" }	},
		{	"crimson",			{ "#dc143c", "rgb(220,20,60)" }		},
		{	"cyan",				{ "#00ffff", "rgb(0,255,255)" }		},
		{	"darkblue",			{ "#00008b", "rgb(0,0,139)" }		},
		{	"darkcyan",			{ "#008b8b", "rgb(0,139,139)" }		},
		{	"darkgoldenrod",	{ "#b8860b", "rgb(184,134,11)" }	},
		{	"darkgray",			{ "#a9a9a9", "rgb(169,169,169)" }	},
		{	"darkgreen",		{ "#006400", "rgb(0,100,0)" }		},
		{	"darkgrey",			{ "#a9a9a9", "rgb(169,169,169)" }	},
		{	"darkkhaki",		{ "#bdb76b", "rgb(189,183,107)" }	},
		{	"darkmagenta",		{ "#8b008b", "rgb(139,0,139)" }		},
		{	"darkolivegreen",	{ "#556b2f", "rgb(85,107,47)" }		},
		{	"darkorange",		{ "#ff8c00", "rgb(255,140,0)" }		},
		{	"darkorchid",		{ "#9932cc", "rgb(153,50,204)" }	},
		{	"darkred",			{ "#8b0000", "rgb(139,0,0)" }		},
		{	"darksalmon",		{ "#e9967a", "rgb(233,150,122)" }	},
		{	"darkseagreen",		{ "#8fbc8f", "rgb(143,188,143)" }	},
		{	"darkslateblue",	{ "#483d8b", "rgb(72,61,139)" }		},
		{	"darkslategray",	{ "#2f4f4f", "rgb(47,79,79)" }		},
		{	"darkslategrey",	{ "#2f4f4f", "rgb(47,79,79)" }		},
		{	"darkturquoise",	{ "#00ced1", "rgb(0,206,209)" }		},
		{	"darkviolet",		{ "#9400d3", "rgb(148,0,211)" }		},
		{	"deeppink",			{ "#ff1493", "rgb(255,20,147)" }	},
		{	"deepskyblue",		{ "#00bfff", "rgb(0,191,255)" }		},
		{	"dimgray",			{ "#696969", "rgb(105,105,105)" }	},
		{	"dimgrey",			{ "#696969", "rgb(105,105,105)" }	},
		{	"dodgerblue",		{ "#1e90ff", "rgb(30,144,255)" }	},
		{	"firebrick",		{ "#b22222", "rgb(178,34,34)" }		},
		{	"floralwhite",		{ "#fffaf0", "rgb(255,250,240)" }	},
		{	"forestgreen",		{ "#228b22", "rgb(34,139,34)" }		},
		{	"fuchsia",			{ "#ff00ff", "rgb(255,0,255)" }		},
		{	"gainsboro",		{ "#dcdcdc", "rgb(220,220,220)" }	},
		{	"ghostwhite",		{ "#f8f8ff", "rgb(248,248,255)" }	},
		{	"gold",				{ "#ffd700", "rgb(255,215,0)" }		},
		{	"goldenrod",		{ "#daa520", "rgb(218,165,32)" }	},
		{	"gray",				{ "#808080", "rgb(128,128,128)" }	},
		{	"green",			{ "#008000", "rgb(0,128,0)" }		},
		{	"greenyellow",		{ "#adff2f", "rgb(173,255,47)" }	},
		{	"grey",				{ "#808080", "rgb(128,128,128)" }	},
		{	"honeydew",			{ "#f0fff0", "rgb(240,255,240)" }	},
		{	"hotpink",			{ "#ff69b4", "rgb(255,105,180)" }	},
		{	"indianred",		{ "#cd5c5c", "rgb(205,92,92)" }		},
		{	"indigo",			{ "#4b0082", "rgb(75,0,130)" }		},
		{	"ivory",			{ "#fffff0", "rgb(255,255,240)" }	},
		{	"khaki",			{ "#f0e68c", "rgb(240,230,140)" }	},
		{	"lavender",			{ "#e6e6fa", "rgb(230,230,250)" }	},
		{	"lavenderblush",	{ "#fff0f5", "rgb(255,240,245)" }	},
		{	"lawngreen",		{ "#7cfc00", "rgb(124,252,0)" }		},
		{	"lemonchiffon",		{ "#fffacd", "rgb(255,250,205)" }	},
		{	"lightblue",		{ "#add8e6", "rgb(173,216,230)" }	},
		{	"lightcoral",		{ "#f08080", "rgb(240,128,128)" }	},
		{	"lightcyan",		{ "#e0ffff", "rgb(224,255,255)" }	},
		{	"lightgoldenrodyellow",	{ "#fafad2", "rgb(250,250,210)" }	},
		{	"lightgray",		{ "#d3d3d3", "rgb(211,211,211)" }	},
		{	"lightgreen",		{ "#90ee90", "rgb(144,238,144)" }	},
		{	"lightgrey",		{ "#d3d3d3", "rgb(211,211,211)" }	},
		{	"lightpink",		{ "#ffb6c1", "rgb(255,182,193)" }	},
		{	"lightsalmon",		{ "#ffa07a", "rgb(255,160,122)" }	},
		{	"lightseagreen",	{ "#20b2aa", "rgb(32,178,170)" }	},
		{	"lightskyblue",		{ "#87cefa", "rgb(135,206,250)" }	},
		{	"lightslategray",	{ "#778899", "rgb(119,136,153)" }	},
		{	"lightslategrey",	{ "#778899", "rgb(119,136,153)" }	},
		{	"lightsteelblue",	{ "#b0c4de", "rgb(176,196,222)" }	},
		{	"lightyellow",		{ "#ffffe0", "rgb(255,255,224)" }	},
		{	"lime",				{ "#00ff00", "rgb(0,255,0)" }		},
		{	"limegreen",		{ "#32cd32", "rgb(50,205,50)" }		},
		{	"linen",			{ "#faf0e6", "rgb(250,240,230)" }	},
		{	"magenta",			{ "#ff00ff", "rgb(255,0,255)" }		},
		{	"maroon",			{ "#800000", "rgb(128,0,0)" }		},
		{	"mediumaquamarine",	{ "#66cdaa", "rgb(102,205,170)" }	},
		{	"mediumblue",		{ "#0000cd", "rgb(0,0,205)" }		},
		{	"mediumorchid",		{ "#ba55d3", "rgb(186,85,211)" }	},
		{	"mediumpurple",		{ "#9370db", "rgb(147,112,219)" }	},
		{	"mediumseagreen",	{ "#3cb371", "rgb(60,179,113)" }	},
		{	"mediumslateblue",	{ "#7b68ee", "rgb(123,104,238)" }	},
		{	"mediumspringgreen",	{ "#00fa9a", "rgb(0,250,154)" }	},
		{	"mediumturquoise",	{ "#48d1cc", "rgb(72,209,204)" }	},
		{	"mediumvioletred",	{ "#c71585", "rgb(199,21,133)" }	},
		{	"midnightblue",		{ "#191970", "rgb(25,25,112)" }		},
		{	"mintcream",		{ "#f5fffa", "rgb(245,255,250)" }	},
		{	"mistyrose",		{ "#ffe4e1", "rgb(255,228,225)" }	},
		{	"moccasin",			{ "#ffe4b5", "rgb(255,228,181)" }	},
		{	"navajowhite",		{ "#ffdead", "rgb(255,222,173)" }	},
		{	"navy",				{ "#000080", "rgb(0,0,128)" }		},
		{	"oldlace",			{ "#fdf5e6", "rgb(253,245,230)" }	},
		{	"olive",			{ "#808000", "rgb(128,128,0)" }		},
		{	"olivedrab",		{ "#6b8e23", "rgb(107,142,35)" }	},
		{	"orange",			{ "#ffa500", "rgb(255,165,0)" }		},
		{	"orangered",		{ "#ff4500", "rgb(255,69,0)" }		},
		{	"orchid",			{ "#da70d6", "rgb(218,112,214)" }	},
		{	"palegoldenrod",	{ "#eee8aa", "rgb(238,232,170)" }	},
		{	"palegreen",		{ "#98fb98", "rgb(152,251,152)" }	},
		{	"paleturquoise",	{ "#afeeee", "rgb(175,238,238)" }	},
		{	"palevioletred",	{ "#db7093", "rgb(219,112,147)" }	},
		{	"papayawhip",		{ "#ffefd5", "rgb(255,239,213)" }	},
		{	"peachpuff",		{ "#ffdab9", "rgb(255,218,185)" }	},
		{	"peru",				{ "#cd853f", "rgb(205,133,63)" }	},
		{	"pink",				{ "#ffc0cb", "rgb(255,192,203)" }	},
		{	"plum",				{ "#dda0dd", "rgb(221,160,221)" }	},
		{	"powderblue",		{ "#b0e0e6", "rgb(176,224,230)" }	},
		{	"purple",			{ "#800080", "rgb(128,0,128)" }		},
		{	"red",				{ "#ff0000", "rgb(255,0,0)" }		},
		{	"rosybrown",		{ "#bc8f8f", "rgb(188,143,143)" }	},
		{	"royalblue",		{ "#4169e1", "rgb(65,105,225)" }	},
		{	"saddlebrown",		{ "#8b4513", "rgb(139,69,19)" }		},
		{	"salmon",			{ "#fa8072", "rgb(250,128,114)" }	},
		{	"sandybrown",		{ "#f4a460", "rgb(244,164,96)" }	},
		{	"seagreen",			{ "#2e8b57", "rgb(46,139,87)" }		},
		{	"seashell",			{ "#fff5ee", "rgb(255,245,238)" }	},
		{	"sienna",			{ "#a0522d", "rgb(160,82,45)" }		},
		{	"silver",			{ "#c0c0c0", "rgb(192,192,192)" }	},
		{	"skyblue",			{ "#87ceeb", "rgb(135,206,235)" }	},
		{	"slateblue",		{ "#6a5acd", "rgb(106,90,205)" }	},
		{	"slategray",		{ "#708090", "rgb(112,128,144)" }	},
		{	"slategrey",		{ "#708090", "rgb(112,128,144)" }	},
		{	"snow",				{ "#fffafa", "rgb(255,250,250)" }	},
		{	"springgreen",		{ "#00ff7f", "rgb(0,255,127)" }		},
		{	"steelblue",		{ "#4682b4", "rgb(70,130,180)" }	},
		{	"tan",				{ "#d2b48c", "rgb(210,180,140)" }	},
		{	"teal",				{ "#008080", "rgb(0,128,128)" }		},
		{	"thistle",			{ "#d8bfd8", "rgb(216,191,216)" }	},
		{	"tomato",			{ "#ff6347", "rgb(255,99,71)" }		},
		{	"turquoise",		{ "#40e0d0", "rgb(64,224,208)" }	},
		{	"violet",			{ "#ee82ee", "rgb(238,130,238)" }	},
		{	"wheat",			{ "#f5deb3", "rgb(245,222,179)" }	},
		{	"white",			{ "#ffffff", "rgb(255,255,255)" }	},
		{	"whitesmoke",		{ "#f5f5f5", "rgb(245,245,245)" }	},
		{	"yellow",			{ "#ffff00", "rgb(255,255,0)" }		},
		{	"yellowgreen",		{ "#9acd32", "rgb(154,205,50)" }	}
	};

	std::optional<Color> ParseCss(std::string_view s)
	{
		// XXX Should be case-insensitive.
		if (cssColours.contains(s))
		{
			return Color(cssColours[s].first);
		}

		return {};
	}

}
