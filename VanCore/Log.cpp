#define VanCore_EXPORT __declspec(dllexport)
#include "Log.h"
#include <time.h>
#pragma warning(disable:4996)
namespace Van
{
	Log Log::DebugLog;
	Log Log::ErrLog;
	Log::Log() 
	{
		memset(szFile,0,sizeof(szFile));
		m_Mutex =CreateMutex(NULL, FALSE, NULL);
		outputflag=0;
		filesplit=0;
	}

	Log::Log(char *filename,int len,int flag,int split) 
	{
		memset(szFile,0,sizeof(szFile));
		m_Mutex =CreateMutex(NULL, FALSE, NULL);
		outputflag=flag;
		filesplit=split;
		SetLog(filename,len,flag,split);
	}

	Log::~Log() 
	{
		ReleaseMutex(m_Mutex); 
		CloseHandle(m_Mutex); 
	}

	inline int  Log::FormatCurrDate(char *szStr,char *strDay)
	{
		if (szStr==NULL)
			return 1;
		time_t t;
		time(&t);
		struct tm *today;
		today=localtime(&t);
		strftime(szStr,20,"%Y-%m-%d %H:%M:%S",today);
		strftime(strDay,10,"%y%m%d",today);
		return 0;
	}

	int Log::SetLog(char *filename,int len,int flag,int split)
	{
		outputflag=flag;
		filesplit=split;
		if ((len>=128)||(len<=0))
			return -1;
		else
			strncpy(szFile,filename,len);
		return 0;
	}
	int Log::setOutput(int flag)
	{
		outputflag=flag;
		return 0;
	}

	int Log::setSplit(int split)
	{
		filesplit=split;
		return 0;
	}

	int Log::Print(const char* Format,...)
	{
		if(strlen(Format) < 4)
			return 0;
		DWORD d = WaitForSingleObject(m_Mutex, INFINITE); 
		char szBuf[512];
		char szTime[20];
		char szDate[10];
		string fn;

		memset(szBuf,0,sizeof(szBuf));
		memset(szTime,0,sizeof(szTime));
		memset(szDate,0,sizeof(szDate));

		va_list	l_va;
		va_start(l_va,Format);
		vsnprintf(szBuf,sizeof(szBuf),Format,l_va);
		va_end(l_va);

		FormatCurrDate(szTime,szDate);
		if (filesplit==1) 
		{
			fn=szFile;
			fn += ".";
			fn +=szDate;
		}
		else
		{
			fn=szFile;
		}
		if (outputflag==0)
		{
			cout<<szTime<<" : "<<szBuf<<endl;
		}
		else
		{
			ofstream fd;
			try
			{
				fd.open(fn.c_str(),ios::app);
				fd<<szTime<<" : "<<szBuf<<endl;
				fd.close();
			}
			catch(...)
			{
				ReleaseMutex(m_Mutex); 
				cerr<<"open log file exception!"<<endl;
				return -1;
			}
		}
		ReleaseMutex(m_Mutex); 
		return 0;
	}
}