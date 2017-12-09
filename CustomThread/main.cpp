#include <QtCore/QCoreApplication>
#include "CustomThread.h"
#include <QTextStream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	CustomThread t;
	QTextStream in(stdin);
	char c = 0;
	while (1)
	{
		in >> c;
		switch (c)
		{
		case 's':
			t.Start();
			break;
		case 't':
			t.Stop();
			break;
		case 'p':
			t.Pause();
			break;
		case 'r':
			t.Resume();
			break;
		default:
			break;

		}
	}
	return a.exec();
}
