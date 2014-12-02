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
		int			outputflag;		// 0 ��׼�����1 ������ļ� szFile
		int			filesplit;		// 0 �����ļ���1 ������������ļ���1��һ���ļ����Զ��� szFile �����������".yymmdd"
		HANDLE		m_Mutex;
		int			FormatCurrDate(char *szStr,char *strDay);
	public:
		Log();
		Log(char *filename,int len,int flag=1, int split=0);		// filename:��־�ļ�����len: filename �ĳ���, flag: 0 ��׼�����1 ������ļ�
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