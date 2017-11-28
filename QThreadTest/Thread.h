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

private:
	QMutex m_mutex;
};
