
#include <Windows.h>
#include <WinInet.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;
#include "VersionManager.h"
#include "WWW.h"
#pragma warning(disable:4996)

#pragma comment(lib,"Wininet.lib")

namespace Van
{
	VersionManager::VersionManager()
	{
		memset(m_szDownLoadUrlBase,0,sizeof(m_szDownLoadUrlBase));
		memset(m_szVersionConfig,0,sizeof(m_szVersionConfig));
		memset(m_szUpdateList,0,sizeof(m_szUpdateList));
		fstream f;
		f.open("Van.vw");
		string strTemp;
		f>>strTemp;
		f>>strTemp;
		memcpy(m_szDownLoadUrlBase,strTemp.c_str(),strlen(strTemp.c_str()));
		f>>strTemp;
		memcpy(m_szVersionConfig,strTemp.c_str(),strlen(strTemp.c_str()));
		f>>strTemp;
		memcpy(m_szUpdateList,strTemp.c_str(),strlen(strTemp.c_str()));
		f.close();
		m_nAOIVersion=0;
	}
	void VersionManager::TryToUpdate()
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE	hFind = FindFirstFile(TEXT("AOI.vw"), &FindFileData);

		if (hFind == INVALID_HANDLE_VALUE) {
			//printf ("Invalid File Handle. Get Last Error reports %d \n", GetLastError ());
		} else {
			FindClose(hFind);
			fstream f;
			f.open("AOI.vw");
			string version;
			f>>version;
			f.close();
			m_nAOIVersion=atoi(version.c_str());
		}

		if (CheckIsThereANewVersion())
		{
			UpdateToLatestRelease();
		}
	}

	bool VersionManager::CheckIsThereANewVersion()
	{
		char	szUrl[256];
		char	szBuffer[64];
		memset(szBuffer,0,sizeof(szBuffer));
		memset(szUrl,0,sizeof(szUrl));
		memcpy(szUrl,m_szDownLoadUrlBase,strlen(m_szDownLoadUrlBase));
		WWW www;
		www.Download(strcat(szUrl,m_szVersionConfig),szBuffer);
		return atoi(szBuffer)>m_nAOIVersion?true:false;
	}

	void VersionManager::GetUpdateList(char *szBuffer)
	{
		char szUrl[256];
		memset(szUrl,0,sizeof(szUrl));
		memcpy(szUrl,m_szDownLoadUrlBase,strlen(m_szDownLoadUrlBase));
		WWW www;
		www.Download(strcat(szUrl,m_szUpdateList),szBuffer);
	}

	void VersionManager::UpdateToLatestRelease()
	{
		char szUpdateLists[1024];
		memset(szUpdateLists,0,sizeof(szUpdateLists));
		GetUpdateList(szUpdateLists);
		char *tempPos=NULL;
		char *tempIndex=szUpdateLists;
		vector<UpdateCommand>	tasks;
		string strCmd;
		UpdateCommand			uc;
		while(true)
		{
			if(memcmp(tempIndex,"end",strlen("end"))==0)
			{
				break;
			}
			tempPos=strchr(tempIndex,' ');
			memcpy(uc.szCmd,tempIndex,tempPos-tempIndex);
			tempIndex=tempPos+1;
			tempPos=strchr(tempIndex,' ');
			memcpy(uc.szTarget,tempIndex,tempPos-tempIndex);
			tempIndex=tempPos+1;
			tempPos=strchr(tempIndex,'\n');
			memcpy(uc.szReserved,tempIndex,tempPos-tempIndex);
			tempIndex=tempPos+1;
			tasks.push_back(uc);
			uc.Reset();
		}
		unsigned int nCount=tasks.size();
		WWW www;
		char szUrl[256];
		for (unsigned int i=0;i<nCount;i++)
		{
			if (memcmp(tasks[i].szCmd,"download",strlen("download"))==0)
			{
				memset(szUrl,0,sizeof(szUrl));
				memcpy(szUrl,m_szDownLoadUrlBase,strlen(m_szDownLoadUrlBase));
				cout<<tasks[i].szCmd<<"-----------:"<<tasks[i].szTarget+1<<endl;
				www.DownloadAndLocate(strcat(szUrl,tasks[i].szTarget),tasks[i].szReserved);
			}
			else if (memcmp(tasks[i].szCmd,"move",strlen("move"))==0)
			{
				strCmd="move ";
				strCmd+=string(tasks[i].szTarget);
				strCmd+=" ";
				strCmd+=string(tasks[i].szReserved);
				cout<<"Updating the module---------->:"<<tasks[i].szReserved<<endl;
				system(strCmd.c_str());
			}
			else if (memcmp(tasks[i].szCmd,"del",strlen("del"))==0)
			{
				strCmd="del ";
				strCmd+=string(tasks[i].szTarget);
				system(strCmd.c_str());
			}
			else if (memcmp(tasks[i].szCmd,"mkdir",strlen("mkdir"))==0)
			{
				strCmd="mkdir ";
				strCmd+=string(tasks[i].szTarget);
				system(strCmd.c_str());
			}
		}
		cout<<"Updating done!"<<endl;
	}
}