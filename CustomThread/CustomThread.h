/*
* Description: 自定义线程，增加了暂停恢复，安全退出等QThread没有的功能
* Author: 公子开明 KaiMing Prince
* Detail: 默认的QThread并不具有暂停运行线程和恢复运行的功能，，且关闭线程的方式可能出现未定义行为，子类化添加效果
* Class： CustomThread
* Implement: 本类实现了QThread的附加功能处理
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
