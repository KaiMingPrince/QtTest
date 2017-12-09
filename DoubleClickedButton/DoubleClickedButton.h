/*
* Description: �ֿ���Ӧ������˫����QPushButton
* Author: ���ӿ��� KaiMing Prince
* Detail: Ĭ�ϵ�QPushButton��˫���¼�����ǰ���ȴ��������¼���Ӱ�����������ķֱ���
* Class�� DoubleClickedButton
* Implement: ����ʵ����QPushButton˫���͵����ķֱ����¼�
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