#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include <iostream>
#include <list>
#include <string>
#include <windows.h>
using namespace  std;
namespace Van
{
	class VanCore_EXPORT Directory
	{
	public:
		static	 bool				Exsit(string strPath);
		static	list<string>		GetAllFilesInThisDirectory(string strPath);
	};
}