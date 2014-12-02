#define VanCore_EXPORT  _declspec(dllexport)
#include "VersionManager.h"
#include "Log.h"

namespace Van
{
	VersionManager::VersionManager()
	{
		memset(m_szDownLoadUrlBase,0,sizeof(m_szDownLoadUrlBase));
		memset(m_szVersionConfig,0,sizeof(m_szVersionConfig));
		memset(m_szUpdateList,0,sizeof(m_szUpdateList));
		fstream f;
		f.open("AOI.vw");
		string strTemp;
		f>>strTemp;
		f>>strTemp;
		memcpy(m_szDownLoadUrlBase,strTemp.c_str(),strlen(strTemp.c_str()));
		f>>strTemp;
		memcpy(m_szVersionConfig,strTemp.c_str(),strlen(strTemp.c_str()));
		f>>strTemp;
		memcpy(m_szUpdateList,strTemp.c_str(),strlen(strTemp.c_str()));
		f.close();
		m_nUpdaterVersion=0;
	}
	void VersionManager::TryToUpdate()
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE	hFind = FindFirstFile(TEXT("AOI.vw"), &FindFileData);

		if (hFind == INVALID_HANDLE_VALUE) {
			printf ("Invalid File Handle. Get Last Error reports %d ", GetLastError ());
		} else {
			FindClose(hFind);
			fstream f;
			f.open("Van.vw");
			string version;
			f>>version;
			f.close();
			m_nUpdaterVersion=atoi(version.c_str());
		}
		Log::DebugLog.Print("Updater version is %d",m_nUpdaterVersion);
		if (CheckIsThereANewVersion())
		{
			Log::DebugLog.Print("Update Updater");
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
		return atoi(szBuffer)>m_nUpdaterVersion?true:false;
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
		}
		cout<<"Updating done!"<<endl;
	}
}