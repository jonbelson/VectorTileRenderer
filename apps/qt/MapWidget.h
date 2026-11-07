
#ifndef MAP_WIDGET_H
#define MAP_WIDGET_H

#include <QOpenGLWidget>

class MapWidgetViewModel;


class MapWidget : public QOpenGLWidget
{
	Q_OBJECT

	public:
		MapWidget(QWidget* parent);
		virtual ~MapWidget();

		void SetUri(QString uri);

	protected:
		virtual void paintEvent(QPaintEvent* event) override;
		virtual void resizeEvent(QResizeEvent* event) override;

		virtual void mouseMoveEvent(QMouseEvent *event) override;
		virtual void wheelEvent(QWheelEvent *event) override;
		virtual void mousePressEvent(QMouseEvent *event) override;
		virtual void mouseReleaseEvent(QMouseEvent *event) override;

	private:
		std::unique_ptr<MapWidgetViewModel> mViewModel;

		float mDpiScale{ 1.0f };

		bool mDragging{ false };
		QPoint mMousePos;
};

#endif	// MAP_WIDGET_H

