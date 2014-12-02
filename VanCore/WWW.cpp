#define VanCore_EXPORT _declspec(dllexport)

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

	void WWW::DownloadAndLocate(char *szUrl,char *szPath)
	{
		HINTERNET hSession = InternetOpen(TEXT("DownLoadAndLocate"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		char	szbuffer[10240]="";
		if(hSession != NULL)
		{
			HINTERNET hHttp = InternetOpenUrlA(hSession, szUrl, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			if (hHttp != NULL)
			{
				BOOL   bHwrite;
				DWORD  dwWritten;
				HANDLE hCreatefile;
				hCreatefile = CreateFileA(szPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
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
					internetreadfile = InternetReadFile(hHttp, szbuffer, sizeof(szbuffer), &dwTeread);
					if(!dwTeread)
						break;

					bHwrite = WriteFile(hCreatefile, szbuffer, sizeof(szbuffer), &dwWritten, NULL);
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