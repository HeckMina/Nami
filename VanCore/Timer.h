#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include "VanCoreDependences.h"

namespace Van
{
	class	Timer
	{
	private:
		LARGE_INTEGER	m_StartTime;
		LARGE_INTEGER	m_StopTime;
		LARGE_INTEGER	m_Frequency;
	public:
		BOOL			Init();
		BOOL			Start();
		float			GetElapsedTime(BOOL bReset);
	};
}