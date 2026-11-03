
#include "MapWidget.h"

#include <memory>

#include <QPainter>
#include <QResizeEvent>

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
	int mWidth{1};
	int mHeight{1};

	int mZoom{ 14 };
	double mLatitude{ 51.51525477169754 };
	double mLongitude{ -0.14226616509484685 };

	std::shared_ptr<mvt::style::Style> mStyle;
	std::unique_ptr<rendering::qt::QtRenderTarget> mRenderTarget;
	std::unique_ptr<mvt::renderer::RenderContext> mRenderContext;
	std::unique_ptr<mvt::renderer::Renderer> mRenderer;
		
public:
	MapWidgetViewModel()
	{
		auto [x, y] = mvt::tile::LatLongToTileF(mZoom, mLatitude, mLongitude);

		SetSize(100, 100);

		// https://openfreemap.org
		SetServerAddress("https://tiles.openfreemap.org/styles/liberty");
	}

	~MapWidgetViewModel()
	{
		mvt::tile::ShutdownProtobuf();
	}

	void SetSize(int width, int height)
	{
		mWidth = width;
		mHeight = height;

		mRenderContext = nullptr;
		mRenderTarget = nullptr;

		mRenderTarget = std::make_unique<rendering::qt::QtRenderTarget>(width, height);

		if (mStyle)
		{
			mRenderContext = std::make_unique<mvt::renderer::RenderContext>(*mRenderTarget, *mStyle, 1.0f);
		}
	}

	bool SetServerAddress(std::string uri)
	{
		if (!mRenderTarget) return false;

		auto style = mvt::style::Style::LoadFromUri(uri);
		if (!style) return false;

		mStyle = style;

		mRenderContext = nullptr;
		mRenderContext = std::make_unique<mvt::renderer::RenderContext>(*mRenderTarget, *mStyle, 1.0f);

		mRenderer = nullptr;
		mRenderer = std::make_unique<mvt::renderer::Renderer>(mStyle.get());

		return true;
	}

	bool Render(QPainter* painter)
	{
		if (!painter) return false;
		if (!mStyle) return false;

		auto [x, y] = mvt::tile::LatLongToTile(mZoom, mLatitude, mLongitude);

		mvt::tile::TileSpecArray tileSpecArray;

		mvt::tile::TileSpec tileSpec{.zoom = mZoom, .y = y, .x = x};
		tileSpecArray.push_back(tileSpec);



		mRenderTarget->Begin(painter);
		mRenderer->RenderTiles(*mRenderContext.get(), tileSpecArray, static_cast<float>(mZoom));
		mRenderTarget->End();

		return true;
	}

};



MapWidget::MapWidget(QWidget* parent)
	: QOpenGLWidget(parent)
{

	setAutoFillBackground(false);



	mViewModel = std::make_unique<MapWidgetViewModel>();
}

MapWidget::~MapWidget()
{

}

void MapWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter;

	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);

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


