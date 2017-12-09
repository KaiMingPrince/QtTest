/*
* Description: 分开响应单击和双击的QPushButton
* Author: 公子开明 KaiMing Prince
* Detail: 默认的QPushButton，双击事件触发前会先触发单击事件，影响两个操作的分别处理
* Class： DoubleClickedButton
* Implement: 本类实现了QPushButton双击和单击的分别处理事件
*/
#ifndef _DOUBLE_CLICKED_BUTTON_H__
#define _DOUBLE_CLICKED_BUTTON_H__
#include <QPushButton>

class QTimer;

class DoubleClickedButton : public QPushButton
{
	Q_OBJECT

public:
	DoubleClickedButton(QWidget *parent=Q_NULLPTR);
	DoubleClickedButton(const QString &text, QWidget *parent = Q_NULLPTR);
	DoubleClickedButton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);

	~DoubleClickedButton();

protected:
	virtual bool event(QEvent* event);

signals:
	void singleClicked();
	void doubleClicked();

private:
	bool			m_bDoubleClicked;
	QTimer*			m_single_clicked_timer;
};
#endif //_DOUBLE_CLICKED_BUTTON_H__