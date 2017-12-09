#include "DoubleClickedButton.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QWidget* pMainWidget = new QWidget;
	QVBoxLayout* pMainLayout = new QVBoxLayout(pMainWidget);
	DoubleClickedButton* pBtn = new DoubleClickedButton("Double Click", pMainWidget);
	pMainLayout->addWidget(pBtn, 10);
	QLabel* pOutputLabel = new QLabel("Output", pMainWidget);
	pMainLayout->addWidget(pOutputLabel, 1);
	QObject::connect(pBtn, &DoubleClickedButton::singleClicked, std::bind(&QLabel::setText, pOutputLabel, "Simple Clicked"));
	QObject::connect(pBtn, &DoubleClickedButton::doubleClicked, std::bind(&QLabel::setText, pOutputLabel, "Double Clicked"));
	pMainWidget->resize(140, 100);
	pMainWidget->show();
	return a.exec();
}
