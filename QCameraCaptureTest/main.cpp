#include "CameraCapture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CameraCapture c;
	//c.start();
	return a.exec();
}