#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;
namespace Van
{
	class VanCore_EXPORT Utils
	{
	public:
		static string GetInstallationOf(const char *pName="com.unity3d.kharma\\DefaultIcon");
	};
}