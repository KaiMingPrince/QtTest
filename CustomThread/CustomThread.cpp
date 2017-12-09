#include "CustomThread.h"

CustomThread::CustomThread(QObject *parent)
	: QThread(parent),
	  m_bPause(false),
	  m_bTerminate(false)
{
}

CustomThread::~CustomThread()
{
}

void CustomThread::Start()
{
	printf("Thread Start\n");
	m_bTerminate = false;
	start();
}

void CustomThread::Stop()
{
	printf("Thread Stopped\n");
	Resume();
	m_bTerminate = true;
	wait();
}

void CustomThread::Pause()
{
	if (!m_bPause)
	{
		m_bPause = true;
		m_mutex.lock();
		printf("Thread is paused\n");
	}
	else
	{
		printf("Thread is already paused\n");
	}
}

void CustomThread::Resume()
{
	if (m_bPause)
	{
		m_bPause = false;
		m_mutex.unlock();
		printf("Thread is resumed\n");
	}
	else
	{
		printf("Thread is not paused\n");
	}
}

void CustomThread::run()
{
	unsigned long index = 0;
	while (true)
	{
		if (m_bTerminate)
		{
			break;
		}
		QMutexLocker locker(&m_mutex);
		printf("Thread is Running %d\n", ++index);
	}
}