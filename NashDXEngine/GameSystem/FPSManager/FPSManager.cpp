///////////////////////////////////////////////////////////////////////////////
// Filename: FPSManager.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FPSManager.h"

FPSManager* FPSManager::instance;

FPSManager::FPSManager()
{
	if (instance) {
		delete this;
	}
	else instance = this;
}


FPSManager::FPSManager(const FPSManager& other)
{
}


FPSManager::~FPSManager()
{
	Shutdown();
}


bool FPSManager::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	return true;
}

void FPSManager::Shutdown()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = 0;
}

void FPSManager::Frame()
{
	m_count++;

	if (timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;

		m_startTime = timeGetTime();
	}
}


int FPSManager::GetFps()
{
	return m_fps;
}