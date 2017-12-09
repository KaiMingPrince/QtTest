/*
* Description: �Զ����̣߳���������ͣ�ָ�����ȫ�˳���QThreadû�еĹ���
* Author: ���ӿ��� KaiMing Prince
* Detail: Ĭ�ϵ�QThread����������ͣ�����̺߳ͻָ����еĹ��ܣ����ҹر��̵߳ķ�ʽ���ܳ���δ������Ϊ�����໯���Ч��
* Class�� CustomThread
* Implement: ����ʵ����QThread�ĸ��ӹ��ܴ���
*/
#include <QThread>
#include <QMutex>

class CustomThread : public QThread
{
	Q_OBJECT

public:
	CustomThread(QObject *parent=Q_NULLPTR);
	~CustomThread();

	void Start();
	void Stop();
	void Pause();
	void Resume();

protected:
	virtual void run();

private:
	QMutex				m_mutex;
	bool				m_bPause;
	bool				m_bTerminate;
};
