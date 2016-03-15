///////////////////////////////////////////////////////////////////////////////
// Filename: TimerManager.cpp
///////////////////////////////////////////////////////////////////////////////
#include "TimerManager.h"

TimerManager* TimerManager::instance;

TimerManager::TimerManager()
{
	if (instance) {		//Singleton
		delete this;
	}
	else instance = this;

}


TimerManager::TimerManager(const TimerManager& other)
{
}


TimerManager::~TimerManager()
{
}


bool TimerManager::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}


void TimerManager::Frame()
{
	INT64 currentTime;
	float timeDifference;


	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}


float TimerManager::GetTime()
{
	return m_frameTime;
}