export module core.geometry;

import std;

export namespace core::geometry
{
	export struct Vector
	{
		float i{};
		float j{};

		Vector operator*(float f) const
		{
			return Vector{ i * f,  j * f };
		}
	};

	export struct Point
	{
		float x;
		float y;

		static float Distance(const Point& p1, const Point& p2)
		{
			return std::sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
		}

		Vector operator-(const Point& p) const
		{
			return Vector{x - p.x, y - p.y};
		}

		Point operator+(const Vector& v) const
		{
			return Point { x + v.i, y + v.j };
		}
	};

	export struct Rect
	{
		float x{};
		float y{};
		float width{};
		float height{};

		Rect() {}

		Rect(const Point& topLeft, float width, float height) : Rect(topLeft.x, topLeft.y, width, height) {}

		Rect(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height) {}

		static Rect CreateCentred(const Point& centre, float w, float h)
		{
			return Rect(centre.x - w/2, centre.y - h/2, w, h);
		}

		void Offset(float dx, float dy)
		{
			x -= dx;
			y -= dy;
		}

		void Inflate(float dx, float dy)
		{
			x -= dx;
			y -= dx;
			width += 2*dx;
			height += 2*dy;
		}

		Point Centre(void) const { return { x + width/2, y + height/2 }; }
		float Right(void) const { return x + width; }
		float Bottom(void) const { return y + height; }

		Point TopLeft(void) const { return Point(x, y); }
		Point TopRight(void) const { return Point(Right(), y); }
		Point BottomRight(void) const { return Point(Right(), Bottom()); }
		Point BottomLeft(void) const { return Point(x, Bottom()); }

		bool IsEmpty(void) const
		{
			return width == 0.0f && height == 0.0f;
		}

		bool IsInside(const Point& p) const
		{
			return p.x >= x && p.x < x+width && p.y >= y && p.y < y+height;
		}

		bool Intersects(const Rect& rect) const
		{
			if (rect.Right() < x || rect.x > Right() || rect.y > Bottom() || rect.Bottom() < y)
				return false;

			return true;
		}

		bool IsInside(const Rect& rect) const
		{
			if (IsInside(rect.TopLeft()) && IsInside(rect.TopRight()) && IsInside(rect.BottomRight()) && IsInside(rect.BottomLeft()))
				return true;

			return false;
		}

	};

	export enum struct GeometryType
	{
		None, MultiPoint, LineString, MultiPolygon
	};

	export using PointArray = std::vector<Point>;

	export struct MultiPoint
	{
		PointArray points;
	};

	export struct LineString
	{
		std::vector<PointArray> lines;
	};

	export struct Polygon
	{
		PointArray exteriorRing;

		std::vector<PointArray> interiorRings;
	};

	export struct MultiPolygon
	{
		std::vector<Polygon> polygons;
	};

}
