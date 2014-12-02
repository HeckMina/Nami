#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT __declspec(dllimport)
#endif
#include <iostream>
#include <stdarg.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

namespace Van
{
	class VanCore_EXPORT Log
	{
	private:
		char		szFile[128];
		int			outputflag;		// 0 标准输出，1 输出到文件 szFile
		int			filesplit;		// 0 单个文件，1 按照日期输出文件，1天一个文件（自动在 szFile 后面加上日期".yymmdd"
		HANDLE		m_Mutex;
		int			FormatCurrDate(char *szStr,char *strDay);
	public:
		Log();
		Log(char *filename,int len,int flag=1, int split=0);		// filename:日志文件名，len: filename 的长度, flag: 0 标准输出，1 输出到文件
		~Log();
		int SetLog(char *filename,int len,int flag=1, int split=0);
		int setOutput(int flag);
		int setSplit(int split);
		int Print(const char* Format, ...);
	public:
		static		Log		DebugLog;
		static		Log		ErrLog;
	};
}