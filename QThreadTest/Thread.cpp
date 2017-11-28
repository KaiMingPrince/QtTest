#include "Thread.h"

Thread::Thread(QObject *parent)
	: QThread(parent)
{
}

Thread::~Thread()
{
}

void Thread::Pause()
{
	if (m_mutex.tryLock(1));
	printf("Thread Pause\n");
}

void Thread::Resume()
{
	m_mutex.unlock();
	printf("Thread Resume\n");
}

void Thread::run()
{
	printf("Thread Start\n");
	int index = 0;
	while (true)
	{
		m_mutex.lock();
		printf("Thread is Running %d\n", ++index);
		m_mutex.unlock();
	}
}