
#include "Window.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QSurfaceFormat fmt;
	fmt.setSamples(4);
	QSurfaceFormat::setDefaultFormat(fmt);

	Window window;
	window.resize(640, 640);
	window.show();

	return app.exec();
}

