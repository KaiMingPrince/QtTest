#include "DoubleClickedButton.h"
#include <QEvent>
#include <QTimer>

DoubleClickedButton::DoubleClickedButton(QWidget *parent)
	: QPushButton(parent),
	  m_single_clicked_timer(new QTimer(this)),
	  m_bDoubleClicked(false)
{
	m_single_clicked_timer->setSingleShot(true);
	connect(m_single_clicked_timer, SIGNAL(timeout()), this, SIGNAL(singleClicked()));
}

DoubleClickedButton::DoubleClickedButton(const QString &text, QWidget *parent)
	: DoubleClickedButton(parent)
{
	setText(text);
}

DoubleClickedButton::DoubleClickedButton(const QIcon &icon, const QString &text, QWidget *parent)
	: DoubleClickedButton(text, parent)
{
	setIcon(icon);
}

DoubleClickedButton::~DoubleClickedButton()
{
}

bool DoubleClickedButton::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::MouseButtonRelease:
		m_bDoubleClicked ? m_bDoubleClicked = false//����ǵڶ��ν��룬����״̬
			/*������Ҫһ����ʱ�жϣ���ʱ��û����MouseButtonDblClick�¼������ǵ���Ч��*/
			: m_single_clicked_timer->start(10);//���Է��ּ��ʱ����ò�Ҫ����10ms�����򲻹������¼��ķ�������������Ҫ�ӳ٣����������޸ļ��ʱ��
		break;
	case QEvent::MouseButtonDblClick:
		m_single_clicked_timer->stop();//����˫���¼�ֹͣ����ʱ��
		m_bDoubleClicked = true;
		emit doubleClicked();
		break;
	default:
		break;
	}

	return QPushButton::event(event);
}
