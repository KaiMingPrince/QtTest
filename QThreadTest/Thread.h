#pragma once

#include <QThread>
#include <QWaitCondition>
#include <QMutex>



class Thread : public QThread
{
	Q_OBJECT

public:
	Thread(QObject *parent=Q_NULLPTR);
	~Thread();
	void Pause();
	void Resume();

protected:
	virtual void run();
};

class SubThread : public QThread
{
	Q_OBJECT

public:
	SubThread(QObject *parent = Q_NULLPTR);
	~SubThread();

protected:
	virtual void run();
	
private:
	QMutex		m_mutex;
	bool		m_bCanPause;
};
