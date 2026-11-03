
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

	protected:
		void paintEvent(QPaintEvent* event) override;
		void resizeEvent(QResizeEvent* event) override;

	private:
		std::unique_ptr<MapWidgetViewModel> mViewModel;
};

#endif	// MAP_WIDGET_H

