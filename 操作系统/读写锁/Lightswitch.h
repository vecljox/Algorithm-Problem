#pragma once
#include <semaphore.h>

class Lightswitch {
public:
	Lightswitch()
		:m_counter{ 0 }
	{
		sem_init(&m_mutex, 0, 1);
	}

	void lock(sem_t& semaphore)
	{
		sem_wait(&m_mutex);
		++m_counter;
		if (m_counter == 1)
		{
			sem_wait(&semaphore);
		}
		sem_post(&m_mutex);
	}

	void unlock(sem_t& semaphore)
	{
		sem_wait(&m_mutex);
		--m_counter;
		if (m_counter == 0)
		{
			sem_post(&semaphore);
		}
		sem_post(&m_mutex);
	}

private:
	int m_counter{};
	sem_t m_mutex{};
};
