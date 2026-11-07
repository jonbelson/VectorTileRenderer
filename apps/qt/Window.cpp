
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "Window.h"

#include "MapWidget.h"


Window::Window()
{
	setWindowTitle("Map Viewer");

	QVBoxLayout* mainBox = new QVBoxLayout();

	QHBoxLayout* controlBox = new QHBoxLayout();

	mEditUri = new QLineEdit();
	mButtonGo = new QPushButton("Go");
	mMapWidget = new MapWidget(this);

	connect(mButtonGo, &QPushButton::clicked, this, &Window::Go);

	controlBox->addWidget(mEditUri);
	controlBox->addWidget(mButtonGo);

	mainBox->addLayout(controlBox);

	mainBox->addWidget(mMapWidget);

	setLayout(mainBox);
}

void Window::Go(void)
{
	QString uri = mEditUri->text();
	if (!uri.isEmpty())
	{
		mMapWidget->SetUri(uri);
	}

}

