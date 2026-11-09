// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

module rendering.qt;

import std;

import core.color;
import core.geometry;
import core.rendertarget;


namespace rendering::qt
{
	using namespace core;
	using namespace core::color;
	using namespace core::geometry;
	using namespace core::rendertarget;


	QColor ToQColor(const Color& color)
	{
		int red = lround(color.Red*255);
		int green = lround(color.Green*255);
		int blue = lround(color.Blue*255);
		int alpha = lround(color.Alpha*255.0f);

		return QColor(red, green, blue, alpha);
	}

	QPointF ToPointF(const core::geometry::Point& point)
	{
		return QPointF(point.x, point.y);
	}

	QRectF ToRectF(const core::geometry::Rect& rect)
	{
		return QRectF(rect.x, rect.y, rect.width, rect.height);
	}

	QRect ToRect(const core::geometry::Rect& rect)
	{
		return QRect(std::lround(rect.x), std::lround(rect.y), std::lround(rect.width), std::lround(rect.height));
	}

	class QtImpl
	{
		int mWidth{};
		int mHeight{};

		QPainter* mPainter{};

		QColor mLineColor;
		QColor mFillColor;
		QColor mFillOutlineColor;

		QPen mLinePen;
		QBrush mFillBrush{Qt::SolidPattern};

		QPixmap mFillPattern;
		QPixmap mLinePattern;

		float mLineOpacity{1.0f};
		float mFillOpacity{1.0f};
		float mLineWidth{1.0f};
		float mCircleRadius{};

		Qt::PenJoinStyle mJoinStyle{Qt::MiterJoin};
		Qt::PenCapStyle mCapStyle{Qt::FlatCap};

		QList<qreal> mDashPattern;

		enum struct LineMode { Colour, Pattern };
		LineMode mLineMode{ LineMode::Colour };

		enum struct FillMode { Solid, Pattern };
		FillMode mFillMode{ FillMode::Solid };

		core::rendertarget::BitmapHandle mNextBitmapHandle = InvalidHandle;
		core::rendertarget::BitmapHandle mBitmapHandle = InvalidHandle;

		std::map<BitmapHandle, std::unique_ptr<QPixmap>> mPixmaps;

		std::stack<QTransform> mTransforms;

		void PushTransform(const QTransform& transform)
		{
			if (mPainter)
			{
				// Push current transforms.
				mTransforms.push(mPainter->transform());

				mPainter->setTransform(transform, true);
			}
		}

		std::vector<QPointF> CreatePointArray(const core::geometry::PointArray& line)
		{
			std::vector<QPointF> points;
			points.reserve(line.size());

			for (const auto& point : line)
			{
				points.emplace_back(ToPointF(point));
			}

			return points;
		}

		QList<QPointF> CreateQList(const geometry::PointArray& outline)
		{
			QList<QPointF> points;
			points.reserve(outline.size());

			auto transformed = outline | std::views::transform([](const Point& p){ return QPointF(p.x, p.y); });

			return QList<QPointF>(transformed.begin(), transformed.end());
		}

		QPolygonF CreatePolygonF(const geometry::PointArray& outline)
		{
			if (!outline.empty())
			{
				auto list = CreateQList(outline);
				list.append(list.front());
				QPolygonF polygon(list);
				return polygon;
			}

			return QPolygonF();
		}

		QPainterPath CreatePainterPath(const geometry::Polygon& polygon)
		{
			QPainterPath path;

			path.addPolygon(CreatePolygonF(polygon.exteriorRing));
			path.closeSubpath();
		
			for (const auto& ring : polygon.interiorRings)
			{
				path.addPolygon(CreatePolygonF(ring));
				path.closeSubpath();
			}

			path.setFillRule(Qt::FillRule::OddEvenFill);
			//path.setFillRule(Qt::FillRule::WindingFill);

			return path;

		}

		QPixmap CreatePixmap(std::shared_ptr<core::bitmap::Bitmap> bitmap)
		{
			if (bitmap)
			{
				using namespace core::bitmap;

				QImage image((const uchar*) bitmap->GetBitmapData().data(), bitmap->GetWidth(), bitmap->GetHeight(),
						QImage::Format_RGBA8888);

				QPixmap pixmap = QPixmap::fromImage(image);

				return pixmap;
			}

			return QPixmap();
		}
	
		void ApplyBrushStyle(QBrush& brush)
		{
			if (mFillMode == FillMode::Solid)
			{
				QColor color(mFillColor);
				color.setAlphaF(mFillOpacity);

				brush.setColor(color);
				brush.setStyle(Qt::BrushStyle::SolidPattern);
			}
			else
			{
				brush.setTexture(mFillPattern);
			}
		}

		void ApplyPenStyle(QPen& pen)
		{
			if (mDashPattern.empty())
			{
				pen.setStyle(Qt::SolidLine);
			}
			else
			{
				pen.setDashPattern(mDashPattern);
			}

			pen.setWidth(mLineWidth);

			if (mLineMode == LineMode::Colour)
			{
				QColor color(mLineColor);
				//color.setAlphaF(mLineOpacity);
				pen.setColor(color);
			}
			else
			{
				QBrush brush(mLinePattern);
				pen.setBrush(brush);
			}
		}

	public:
		QtImpl(int width, int height) : mWidth(width), mHeight(height)
		{

		}

		~QtImpl() {}

		void Begin(QPainter* painter)
		{
			mPainter = painter;
		}

		bool End(void)
		{
			bool valid = mPainter != nullptr;

			mPainter = nullptr;

			return valid;
		}

		void SetLineColor(const Color& color)
		{
			mLineColor = ToQColor(color);
			mLineMode = LineMode::Colour;
		}
	
		void SetLineOpacity(float opacity) { mLineOpacity = opacity; }
		void SetLineWidth(float lineWidth) { mLineWidth = lineWidth; }

		void SetLinePattern(const geometry::Rect& src)
		{
			if (!mPainter) return;

			if (mBitmapHandle == rendertarget::InvalidHandle) return;

			auto it = mPixmaps.find(mBitmapHandle);
			if (it == mPixmaps.end()) return;

			auto pixmap = it->second.get();
			if (!pixmap) return;
			{
				mLinePattern = pixmap->copy(ToRect(src));
				mLineMode = LineMode::Pattern;
			}
		}

		void SetFillColor(const Color& color)
		{
			mFillColor = ToQColor(color);
			mFillMode = FillMode::Solid;
		}

		void SetFillOutlineColor(const Color& color) { mFillOutlineColor = ToQColor(color); }
		void SetFillOpacity(float opacity) { mFillOpacity = opacity; }

		void SetFillPattern(const Rect& src)
		{
			if (!mPainter) return;

			if (mBitmapHandle == rendertarget::InvalidHandle) return;

			auto it = mPixmaps.find(mBitmapHandle);
			if (it == mPixmaps.end()) return;

			auto pixmap = it->second.get();
			if (!pixmap) return;
			{
				mFillPattern = pixmap->copy(ToRect(src));
				mFillMode = FillMode::Pattern;
			}
		}

		Qt::PenCapStyle ToPenCapStyle(LineCap lineCap)
		{
			switch (lineCap)
			{
				case LineCap::Butt:		return Qt::FlatCap;
				case LineCap::Round:	return Qt::RoundCap;
				case LineCap::Square:	return Qt::SquareCap;
			}

			return Qt::SquareCap;
		}

		Qt::PenJoinStyle ToPenJoinStyle(LineJoin lineJoin)
		{
			switch (lineJoin)
			{
				case LineJoin::Bevel:	return Qt::BevelJoin;
				case LineJoin::Round:	return Qt::RoundJoin;
				case LineJoin::Miter:	return Qt::MiterJoin;
				case LineJoin::None:	;
			}			

			return Qt::MiterJoin;
		}

		void SetLineCap(LineCap lineCap)
		{
			mCapStyle = ToPenCapStyle(lineCap);
		}

		void SetLineJoin(LineJoin lineJoin)
		{
			mJoinStyle = ToPenJoinStyle(lineJoin);
		}

		void SetCircleRadius(float circleRadius)
		{
			mCircleRadius = circleRadius;
		}

		void SetDashArray(const std::vector<float>& dashArray)
		{
			mDashPattern.assign(dashArray.begin(), dashArray.end());
		}

		BitmapHandle RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap)
		{
			QPixmap pixmap = CreatePixmap(bitmap);
			if (!pixmap.isNull())
			{
				BitmapHandle handle = ++mNextBitmapHandle;
				mPixmaps[handle] = std::make_unique<QPixmap>(pixmap);
				SetActiveBitmap(handle);
				return handle;
			}

			return InvalidHandle;
		}

		bool UnregisterBitmap(BitmapHandle handle)
		{
			auto it = mPixmaps.find(handle);
			if (it != mPixmaps.end())
			{
				mPixmaps.erase(it);
				return true;
			}
			return false;
		}

		void SetActiveBitmap(BitmapHandle handle)
		{
			mBitmapHandle = handle;
		}

		void FillBackground(void)
		{
			if (mPainter)
			{
				mPainter->save();
				mPainter->resetTransform();
				mPainter->fillRect(0, 0, mWidth, mHeight, mFillColor);
				mPainter->restore();
			}
		}

		void DrawLine(const geometry::LineString* lineString)
		{
			if (mLineWidth == 0.0f) return;

			if (mPainter && lineString)
			{
				for (const auto& line : lineString->lines)
				{
					//if (mLineMode == LineMode::Pattern)
					//{


					//}
					//else if (mLineMode == LineMode::Colour)
					{
						ApplyPenStyle(mLinePen);

						mLinePen.setColor(mLineColor);
						mPainter->setPen(mLinePen);

						auto points = CreatePointArray(line);
						mPainter->drawPolyline(points.data(), static_cast<int>(points.size()));
					}
				}
			}
		}

		void DrawPolygon(const geometry::Polygon& polygon)
		{
			if (mPainter)
			{
				ApplyPenStyle(mLinePen);

				mLinePen.setColor(mLineColor);

				mPainter->setPen(mLinePen);
				mPainter->setBrush(Qt::NoBrush);

				auto exterior = CreatePointArray(polygon.exteriorRing);
				mPainter->drawPolygon(exterior.data(), static_cast<int>(exterior.size()));

				for (const auto& interior : polygon.interiorRings)
				{
					auto points = CreatePointArray(interior);
					mPainter->drawPolygon(points.data(), static_cast<int>(points.size()));

				}
			}
		}

		void FillPolygon(const geometry::Polygon& polygon)
		{
			if (mPainter)
			{
				ApplyBrushStyle(mFillBrush);

				auto path = CreatePainterPath(polygon);
				mPainter->fillPath(path, mFillBrush);
			}
		}

		void DrawBitmap(const geometry::Rect& dest)
		{
			if (mBitmapHandle == rendertarget::InvalidHandle) return;

			auto it = mPixmaps.find(mBitmapHandle);
			if (it == mPixmaps.end()) return;

			auto pixmap = it->second.get();
			if (!pixmap) return;

			if (mPainter)
			{
				mPainter->drawPixmap(ToRect(dest), *pixmap);
			}
		}

		void DrawBitmap(const geometry::Rect& src, const geometry::Rect& dest)
		{
			if (mBitmapHandle == rendertarget::InvalidHandle) return;

			auto it = mPixmaps.find(mBitmapHandle);
			if (it == mPixmaps.end()) return;

			auto pixmap = it->second.get();
			if (!pixmap) return;

			if (mPainter)
			{
				mPainter->drawPixmap(ToRectF(dest), *pixmap, ToRectF(src));
			}
		}

		void DrawSymbolWithRGB(const geometry::Rect& src, const geometry::Rect& dest, const Color& colour)
		{
			if (src.IsEmpty() || dest.IsEmpty()) return;

			if (mBitmapHandle == rendertarget::InvalidHandle) return;

			auto it = mPixmaps.find(mBitmapHandle);
			if (it == mPixmaps.end()) return;

			auto pixmap = it->second.get();
			if (!pixmap) return;

			if (mPainter)
			{
				QPixmap buffer(src.width, src.height);
				buffer.fill(Qt::transparent);

				{
					QPainter p;
					bool b = p.begin(&buffer);
					if (b)
					{
						p.fillRect(buffer.rect(), ToQColor(colour));

						p.setCompositionMode(QPainter::CompositionMode::CompositionMode_DestinationIn);

						p.drawPixmap(buffer.rect(), *pixmap, ToRect(src));
						p.end();
					}
				}

				mPainter->drawPixmap(ToRectF(dest), buffer, buffer.rect());
			}	
		}

		void PushScale(float scale)
		{
			PushTransform(QTransform::fromScale(scale, scale));
		}

		void PushTranslation(float x, float y)
		{
			PushTransform(QTransform::fromTranslate(x, y));
		}

		void PushRotation(float angleDeg)
		{
			QTransform transform;
			transform.rotate(angleDeg);

			PushTransform(transform);
		}

		void PopTransform(void)
		{
			if (mPainter)
			{
				if (!mTransforms.empty())
				{
					mPainter->setTransform(mTransforms.top());

					mTransforms.pop();
				}
			}
		}

		void ClearTransforms(void)
		{
			if (mPainter)
			{
				mPainter->setTransform(QTransform());
			}
		}

		void SetClipRect(const geometry::Rect& clip)
		{
			if (mPainter) mPainter->setClipRect(ToRectF(clip));
		}

		void ClearClipRect(void)
		{
			if (mPainter) mPainter->setClipping(false);
		}

		void Save(const std::string& outputName)
		{

		}


	};




	// Implementation of QtRenderTarget.
	// A thin wrapper for QtImpl which performs most of the work.
	QtRenderTarget::QtRenderTarget(int width, int height) : mImpl(std::make_unique<QtImpl>(width, height))
	{
		mWidth = width;
		mHeight = height;
	}

	QtRenderTarget::~QtRenderTarget()
	{

	}

	void QtRenderTarget::SetLineColor(const Color& color)
	{
		if (mImpl) mImpl->SetLineColor(color);
	}

	void QtRenderTarget::SetLineOpacity(float opacity)
	{
		if (mImpl) mImpl->SetLineOpacity(opacity);
	}

	void QtRenderTarget::SetLineWidth(float lineWidth)
	{
		if (mImpl) mImpl->SetLineWidth(lineWidth);
	}

	void QtRenderTarget::SetLinePattern(const geometry::Rect& src)
	{
		if (mImpl) mImpl->SetLinePattern(src);
	}

	void QtRenderTarget::SetFillColor(const Color& color)
	{
		if (mImpl) mImpl->SetFillColor(color);
	}

	void QtRenderTarget::SetFillOutlineColor(const Color& color)
	{
		if (mImpl) mImpl->SetFillOutlineColor(color);
	}

	void QtRenderTarget::SetFillOpacity(float opacity)
	{
		if (mImpl) mImpl->SetFillOpacity(opacity);
	}

	void QtRenderTarget::SetFillPattern(const geometry::Rect& src)
	{
		if (mImpl) mImpl->SetFillPattern(src);
	}

	void QtRenderTarget::SetCircleRadius(float circleRadius)
	{
		if (mImpl) mImpl->SetCircleRadius(circleRadius);
	}

	void QtRenderTarget::SetDashArray(const std::vector<float>& dashArray)
	{
		if (mImpl) mImpl->SetDashArray(dashArray);
	}

	void QtRenderTarget::SetLineCap(LineCap lineCap)
	{
		if (mImpl) mImpl->SetLineCap(lineCap);
	}

	void QtRenderTarget::SetLineJoin(LineJoin lineJoin)
	{
		if (mImpl) mImpl->SetLineJoin(lineJoin);
	}

	BitmapHandle QtRenderTarget::RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap)
	{
		if (mImpl)
		{
			return mImpl->RegisterBitmap(bitmap);
		}

		return InvalidHandle;
	}

	bool QtRenderTarget::UnregisterBitmap(BitmapHandle handle)
	{
		if (mImpl)
		{
			return mImpl->UnregisterBitmap(handle);
		}

		return false;
	}

	void QtRenderTarget::SetActiveBitmap(BitmapHandle handle)
	{
		if (mImpl) mImpl->SetActiveBitmap(handle);
	}

	void QtRenderTarget::FillBackground(void)
	{
		if (mImpl) mImpl->FillBackground();
	}

	void QtRenderTarget::DrawLine(const geometry::LineString* lineString)
	{
		if (mImpl && lineString) mImpl->DrawLine(lineString);
	}

	void QtRenderTarget::DrawPolygon(const geometry::MultiPolygon* multiPolygon)
	{
		if (mImpl && multiPolygon)
		{
			for (const auto& polygon : multiPolygon->polygons)
			{
				mImpl->DrawPolygon(polygon);
			}
		}
	}
	void QtRenderTarget::FillPolygon(const geometry::MultiPolygon* multiPolygon)
	{
		if (mImpl && multiPolygon)
		{
			for (const auto& polygon : multiPolygon->polygons)
			{
				mImpl->FillPolygon(polygon);
			}
		}
	}

	void QtRenderTarget::DrawCircle(const geometry::MultiPoint* multiPoint)
	{

	}
	void QtRenderTarget::FillCircle(const geometry::MultiPoint* multiPoint)
	{

	}
	void QtRenderTarget::DrawBitmap(const geometry::Rect& dest)
	{
		if (mImpl) mImpl->DrawBitmap(dest);
	}

	void QtRenderTarget::DrawBitmap(const geometry::Rect& src, const geometry::Rect& dest)
	{
		if (mImpl) mImpl->DrawBitmap(src, dest);
	}

	void QtRenderTarget::DrawSymbolWithRGB(const geometry::Rect& src, const geometry::Rect& dest, const Color& colour)
	{
		if (mImpl) mImpl->DrawSymbolWithRGB(src, dest, colour);
	}

	void QtRenderTarget::PushScale(float scale)
	{
		if (mImpl) mImpl->PushScale(scale);
	}

	void QtRenderTarget::PushTranslation(float x, float y)
	{
		if (mImpl) mImpl->PushTranslation(x, y);
	}

	void QtRenderTarget::PushRotation(float angleDeg)
	{
		if (mImpl) mImpl->PushRotation(angleDeg);
	}

	void QtRenderTarget::PopTransform(void)
	{
		if (mImpl) mImpl->PopTransform();
	}

	void QtRenderTarget::ClearTransforms(void)
	{
		if (mImpl) mImpl->ClearTransforms();
	}

	void QtRenderTarget::SetClipRect(const geometry::Rect& clip)
	{
		if (mImpl) mImpl->SetClipRect(clip);
	}

	void QtRenderTarget::ClearClipRect(void)
	{
		if (mImpl) mImpl->ClearClipRect();
	}

	void QtRenderTarget::Save(const std::string& outputName)
	{

	}

    void QtRenderTarget::Begin(QPainter* painter)
	{
		if (mImpl) mImpl->Begin(painter);
	}

	bool QtRenderTarget::End(void)
	{
		if (mImpl) return mImpl->End();

		return false;
	}


};
