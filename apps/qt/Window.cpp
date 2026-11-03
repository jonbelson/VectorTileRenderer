
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>

#include "Window.h"

#include "MapWidget.h"


Window::Window()
{
	setWindowTitle("Map Viewer");

	

	QVBoxLayout* mMainBox = new QVBoxLayout();
	mMainBox->addWidget(new MapWidget(this));
	//mMainBox->addWidget(new QTextEdit(this));

	setLayout(mMainBox);
}

