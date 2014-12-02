#define VanCore_EXPORT  _declspec(dllexport)


#include "Timer.h"

namespace Van
{
	BOOL	Timer::Init()
	{
		m_StartTime.QuadPart=0;
		return QueryPerformanceFrequency(&m_Frequency);
	}

	BOOL	Timer::Start()
	{
		return QueryPerformanceCounter(&m_StartTime);
	}

	float	Timer::GetElapsedTime(BOOL bReset)
	{
		QueryPerformanceCounter(&m_StopTime);
		float	rTime;
		if (bReset)
		{
			rTime=(float)(m_StopTime.QuadPart-m_StartTime.QuadPart)/m_Frequency.QuadPart;
			m_StartTime.QuadPart=m_StopTime.QuadPart;
		}
		else
		{
			rTime=(float)(m_StopTime.QuadPart-m_StartTime.QuadPart)/m_Frequency.QuadPart;
		}
		return rTime;
	}
}