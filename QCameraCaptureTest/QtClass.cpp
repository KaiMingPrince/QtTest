#include "QtClass.h"
#include <QPainter>

QtClass::QtClass(QWidget *parent)
	: QWidget(parent/*, Qt::FramelessWindowHint*/)
{
	setAttribute(Qt::WA_TranslucentBackground);
}

QtClass::~QtClass()
{
}

void QtClass::paintEvent(QPaintEvent *event)
{
	QPainterPath path;
	path.addRect(QRect(0, 0, 400, 400));
	path.addRect(QRect(100, 100, 200, 200));

	QPainter p(this);
	p.setBrush(Qt::red);
	p.setClipPath(path);
	p.drawRect(QRect(0, 0, 400, 400));
// 	p.setCompositionMode(QPainter::CompositionMode_Clear);
// 	p.fillRect(QRect(100, 100, 200, 200), Qt::SolidPattern);
}
