#include "QtCameraCapture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtCameraCapture c;
	c.CameraCaptureStart();
	return a.exec();
}
