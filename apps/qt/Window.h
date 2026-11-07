#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGroupBox>

class MapWidget;
class QLineEdit;
class QPushButton;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window();

private:
	//QVBoxLayout* mMainBox{};

	QLineEdit* mEditUri{};
	QPushButton* mButtonGo{};
	MapWidget* mMapWidget{};

	void Go(void);
};

#endif	// WINDOW_H

