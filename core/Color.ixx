module;

#include <cassert>
#include <cstdint>
#include <cstdio>

export module core.color;

import std;




export class Color
{
	static Color HslToRgb(int hue, float sat, float light);

public:
	float Red = -1;
	float Green = -1;
	float Blue = -1;
	float Alpha = 1.0f;

	Color() {}
	Color(float r, float g, float b) : Red(r), Green(g), Blue(b) {}
	Color(const std::string& s)
	{
		if (s.length() == 7 && s[0] == '#')
		{
			auto ParseComponent = [](std::string_view sv) -> std::optional<int>
				{
					int result{};
					auto [ptr, ec] = std::from_chars(&sv[0], &sv[0] + 2, result, 16);
					if (ec == std::errc{})
					{
						return result;
					}
					return false;
				};

			auto r = ParseComponent(std::string_view(&s[1], 2));
			auto g = ParseComponent(std::string_view(&s[3], 2));
			auto b = ParseComponent(std::string_view(&s[5], 2));

			if (r.has_value() && g.has_value() && b.has_value())
			{
				Red = r.value() / 255.0f;
				Green = g.value() / 255.0f;
				Blue = b.value() / 255.0f;
			}
		}
		else if (s.size() > 4 && s.find("rgba(") != std::string::npos)
		{
			int r{}, g{}, b{};
			float a{};
			if (sscanf_s(s.c_str(), "rgba(%d,%d,%d,%f)", &r, &g, &b, &a) == 4)
			{
				Red = r / 255.0f;
				Green = g / 255.0f;
				Blue = b / 255.0f;
				Alpha = a;
			}
		}
		else if (s.size() > 5 && s.find("hsla(") != std::string::npos)
		{
			int hue{}, saturation{}, lightness{};
			float a{};

			if (sscanf_s(s.c_str(), "hsla(%d,%d%%,%d%%,%f)", &hue, &saturation, &lightness, &a) == 4)
			{
				Color c = HslToRgb(hue, static_cast<float>(saturation), static_cast<float>(lightness));
				c.Alpha = a;
				*this = c;
			}

		}
		else if (s.size() > 4 && s.find("hsl(") != std::string::npos)
		{
			int hue{}, saturation{}, lightness{};

			if (sscanf_s(s.c_str(), "hsl(%d,%d%%,%d%%)", &hue, &saturation, &lightness) == 3)
			{
				Color c = HslToRgb(hue, static_cast<float>(saturation), static_cast<float>(lightness));
				*this = c;
			}

		}

		///assert(IsValid());
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

// https://www.w3.org/TR/css-color-3/#hsl-color
Color Color::HslToRgb(int hue, float sat, float light)
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
