#include <QtCore/QCoreApplication>
#include "Thread.h"
#include <QTextStream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Thread t;
	t.start();
	QTextStream in(stdin);
	int i = 0;
	while (1)
	{
		in >> i;
		if (0 == i)
		{
			t.Pause();
		}
		else if (1 == i)
		{
			t.Resume();
		}
	}
	return a.exec();
}
