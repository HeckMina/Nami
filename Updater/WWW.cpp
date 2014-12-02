#include <Windows.h>
#include <WinInet.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "WWW.h"

namespace Van
{
	void WWW::Download(char *szUrl,char *szBuffer)
	{
		HINTERNET hSession = InternetOpenA("Download", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if(hSession != NULL)
		{
			HINTERNET hHttp = InternetOpenUrlA(hSession,szUrl, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			if (hHttp != NULL)
			{
				DWORD	dwBufferSize=0;
				InternetReadFile(hHttp, szBuffer, 1024 - 1, &dwBufferSize);
				InternetCloseHandle(hHttp);
				hHttp = NULL;
			}
			else
			{
				cout<<"cannot connect to server!"<<endl;
			}
			InternetCloseHandle(hSession);
			hSession = NULL;
		}
	}
#define MAX_RECV_BUFFER 1024
	void WWW::DownloadAndLocate(char *szUrl,char *szPath)
	{
		HINTERNET hSession = InternetOpen(TEXT("DownLoadAndLocate"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		char	szbuffer[MAX_RECV_BUFFER]="";
		if(hSession != NULL)
		{
			HINTERNET hHttp = InternetOpenUrlA(hSession, szUrl, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			if (hHttp != NULL)
			{
				BOOL   bHwrite;
				DWORD  dwWritten;
				HANDLE hCreatefile;
				hCreatefile = CreateFileA(szPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0);
				if(INVALID_HANDLE_VALUE == hCreatefile)
				{
					cout<<"create file fail"<<endl;
					return ;
				}
				BOOL internetreadfile;
				DWORD dwTeread=0;
				memset(szbuffer,0,sizeof(szbuffer));
				while(true)
				{
					internetreadfile = InternetReadFile(hHttp, szbuffer, MAX_RECV_BUFFER-1, &dwTeread);
					if(!dwTeread)
						break;
					bHwrite = WriteFile(hCreatefile, szbuffer, dwTeread, &dwWritten, NULL);
					if(!bHwrite)
					{
						cout<<"Write to file failed!"<<endl;
						goto ERROR_FILE;
					}
				}
ERROR_FILE:
				CloseHandle(hCreatefile);
				InternetCloseHandle(hHttp);
			}
			InternetCloseHandle(hSession);
			hSession = NULL;
		}
	}
}