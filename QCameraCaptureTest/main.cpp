#include "QCameraCaptureTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCameraCaptureTest w;
	w.show();
	return a.exec();
}
