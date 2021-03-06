////////////////////////////////////////////////////////////////////////////////
// Filename: TimerManager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TimerManager_H_
#define _TimerManager_H_


//////////////
// INCLUDES //
//////////////
#include <windows.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TimerManager
////////////////////////////////////////////////////////////////////////////////
class TimerManager
{
public:
	static TimerManager* getInstance()
	{
		return instance;
	}

	TimerManager();
	TimerManager(const TimerManager&);
	~TimerManager();

	bool Initialize();
	void Frame();

	float GetTime();
	float GetTotalTime();

private:
	static TimerManager* instance;

	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
	float m_totalTime;
};

#endif