#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif

#include <Windows.h>
#include <WinInet.h>
#include <iostream>
using namespace std;

namespace Van
{
	class VanCore_EXPORT WWW
	{
	public:
		void	Download(char *szUrl,char *szBuffer);
		void	DownloadAndLocate(char *szUrl,char *szPath);
	};
}