
#include "MapWidget.h"

#include <memory>

#include <QPainter>
#include <QPainterPath>
#include <QPointF>
#include <QPolygonF>
#include <QResizeEvent>

import core.logger;
import core.rendertarget;
import formats.mvt.style;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import formats.mvt.rendercontext;
import formats.mvt.renderer;
import io.resource;
import rendering.qt;


class MapWidgetViewModel
{
	int mViewWidth{1};
	int mViewHeight{1};

	double mLatitude{ 51.51525477169754 };
	double mLongitude{ -0.14226616509484685 };

	int mZoom{ 14 };
	constexpr static int MinZoom{ 0 };
	constexpr static int MaxZoom{ 22 };

	float mDpiScale{ 1.0f };
	int mTileSize{ 512 };

	std::uint64_t mVisibleCentreX{};
	std::uint64_t mVisibleCentreY{};

	std::shared_ptr<mvt::style::Style> mStyle;
	std::unique_ptr<rendering::qt::QtRenderTarget> mRenderTarget;
	std::unique_ptr<mvt::renderer::RenderContext> mRenderContext;
	std::unique_ptr<mvt::renderer::Renderer> mRenderer;
		
public:
	MapWidgetViewModel(float dpi = 1.0f)
	{
		SetSize(100, 100);

		mDpiScale = dpi;
		mTileSize = lround(dpi*mTileSize);

		auto [x, y] = mvt::tile::LatLongToTileF(mZoom, mLatitude, mLongitude);

		mVisibleCentreX = lround(x*mTileSize);
		mVisibleCentreY = lround(y*mTileSize);

		// https://openfreemap.org
		SetServerAddress("https://tiles.openfreemap.org/styles/liberty");
	}

	~MapWidgetViewModel()
	{
		mvt::tile::ShutdownProtobuf();
	}

	void SetSize(int width, int height)
	{
		mViewWidth = width;
		mViewHeight = height;

		mRenderContext = nullptr;
		mRenderTarget = nullptr;

		mRenderTarget = std::make_unique<rendering::qt::QtRenderTarget>(width, height);

		if (mStyle)
		{
			mRenderContext = std::make_unique<mvt::renderer::RenderContext>(*mRenderTarget, *mStyle, mDpiScale);
		}
	}

	bool SetServerAddress(std::string uri)
	{
		if (!mRenderTarget) return false;

		auto style = mvt::style::Style::LoadFromUri(uri);
		if (!style) return false;

		mStyle = style;

		mRenderContext = nullptr;
		mRenderContext = std::make_unique<mvt::renderer::RenderContext>(*mRenderTarget, *mStyle, mDpiScale);

		mRenderer = nullptr;
		mRenderer = std::make_unique<mvt::renderer::Renderer>(mStyle.get());

		return true;
	}

	void Pan(int iOffX, int iOffY)
	{
		mVisibleCentreX -= iOffX;
		mVisibleCentreY -= iOffY;
	}

	void ZoomIn(void)
	{
		if (mZoom >= MaxZoom) return;

		// GetLat/Long of View centre;
		auto latLong = mvt::tile::TileFToLatLong(mZoom, double(mVisibleCentreX)/mTileSize, double(mVisibleCentreY)/mTileSize);

		mZoom++;

		auto [x, y] = mvt::tile::LatLongToTileF(mZoom, latLong.latitude, latLong.longitude);

		mVisibleCentreX = lround(x*mTileSize);
		mVisibleCentreY = lround(y*mTileSize);

		core::logger::Info(std::format("Zoom = {}\n", mZoom));
	}

	void ZoomOut(void)
	{
		if (mZoom <= MinZoom) return;

		// Get lat/long of View centre.
		auto latLong = mvt::tile::TileFToLatLong(mZoom, double(mVisibleCentreX)/mTileSize, double(mVisibleCentreY)/mTileSize);

		mZoom--;

		auto [x, y] = mvt::tile::LatLongToTileF(mZoom, latLong.latitude, latLong.longitude);

		mVisibleCentreX = lround(x*mTileSize);
		mVisibleCentreY = lround(y*mTileSize);

		core::logger::Info(std::format("Zoom = {}\n", mZoom));
	}

	bool Render(QPainter* painter)
	{
		if (!painter) return false;
		if (!mStyle) return false;


		int iViewCentreX = mViewWidth/2;
		int iViewCentreY = mViewHeight/2;

		uint64_t TLx = (iViewCentreX <= mVisibleCentreX) ? mVisibleCentreX - iViewCentreX : 0;
		uint64_t TLy = (iViewCentreY <= mVisibleCentreY) ? mVisibleCentreY - iViewCentreY : 0;

		int x = static_cast<int>(TLx/mTileSize);
		int y = static_cast<int>(TLy/mTileSize);

		int x2 = static_cast<int>((TLx + mViewWidth)/mTileSize);
		int y2 = static_cast<int>((TLy + mViewHeight)/mTileSize);
		//x2++;
		//y2++;

		int offsetX = static_cast<int>(TLx%mTileSize);
		int offsetY = static_cast<int>(TLy%mTileSize);

		mvt::tile::TileSpecArray tileSpecArray;

		for (int yy=y; yy<=y2; yy++)
		{
			for (int xx=x; xx<=x2; xx++)
			{
				mvt::tile::TileSpec tileSpec { .zoom = mZoom, .y = yy, .x = xx };

				tileSpecArray.emplace_back(tileSpec);
			}
		}


		mRenderTarget->Begin(painter);

		//mRenderTarget->Clear(core::rendertarget::Color("black"));

		mRenderTarget->SetFillColor(core::rendertarget::Color("black"));
		mRenderTarget->FillBackground();

		mRenderTarget->PushTranslation(static_cast<float>(-offsetX), static_cast<float>(-offsetY));

		mRenderer->RenderTiles(*mRenderContext.get(), tileSpecArray, static_cast<float>(mZoom));

		mRenderTarget->PopTransform();

		mRenderTarget->End();

		return true;
	}

};



MapWidget::MapWidget(QWidget* parent)
	: QOpenGLWidget(parent)
{
	///setAutoFillBackground(false);

	mDpiScale = window()->devicePixelRatio();
	mViewModel = std::make_unique<MapWidgetViewModel>(1.0f /*mDpiScale*/);

	setMouseTracking(true);
}

MapWidget::~MapWidget()
{

}

void MapWidget::SetUri(QString uri)
{
	mViewModel->SetServerAddress(uri.toStdString());
}

void MapWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter;

	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);

painter.fillRect(event->rect(), QColor("Pink"));

	QPainterPath path;
	QList<QPointF> points = { {50.0f, 60.0f}, {150.0f, 100.0f}, {120.0f, 150.0f}, {40.0f, 80.0f} };
	QPolygonF polygon(points);
	path.addPolygon(polygon);

	path.closeSubpath();

//	path.setFillRule(Qt::FillRule::OddEvenFill);
//	path.setFillRule(Qt::FillRule::WindingFill);

//	painter.fillPath(path, QBrush(QColor("Red")));

	mViewModel->Render(&painter);

	painter.end();
}

void MapWidget::resizeEvent(QResizeEvent* event)
{
	QOpenGLWidget::resizeEvent(event);

	const QSize newSize = event->size();

	mViewModel->SetSize(newSize.width(), newSize.height());

	update();
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint position = event->position().toPoint();

	if (mDragging)
	{
		int offX = position.x() - mMousePos.x();
		int offY = position.y() - mMousePos.y();

		if (offX || offY)
		{
			mViewModel->Pan(offX, offY);

			update();
		}
	}

	mMousePos = position;
}

void MapWidget::wheelEvent(QWheelEvent *event)
{
	//QOpenGLWidget::wheelEvent(event);

	QPointF position = event->position();

	QPoint pixelDelta = event->pixelDelta();
	QPoint angleDelta = event->angleDelta();

	mMousePos = position.toPoint();

	if (angleDelta.y() != 0)
	{
		if (angleDelta.y() > 0)
		{
			mViewModel->ZoomIn();
		}
		else if(angleDelta.y() < 0)
		{
			mViewModel->ZoomOut();
		}

		update();

		event->accept();
	}
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
	mMousePos = event->position().toPoint();

	if (event->button() == Qt::LeftButton)
	{
		grabMouse();
		mDragging = true;
	}

}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
	mMousePos = event->position().toPoint();

	if (event->button() == Qt::LeftButton)
	{
		mDragging = false;
	}

	releaseMouse();
}


