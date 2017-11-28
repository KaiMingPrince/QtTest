#pragma once

#include <QWidget>

class QtClass : public QWidget
{
	Q_OBJECT

public:
	QtClass(QWidget *parent);
	~QtClass();

protected:
	virtual void paintEvent(QPaintEvent *event);
};
