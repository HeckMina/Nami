#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "WWW.h"

namespace Van
{
	class	VanCore_EXPORT VersionManager
	{
	public:
		VersionManager();
		void	TryToUpdate();
	protected:
		struct	UpdateCommand
		{
			char	szCmd[16];
			char	szTarget[128];
			char	szReserved[128];
			UpdateCommand()
			{
				memset(szCmd,0,sizeof(szCmd));
				memset(szTarget,0,sizeof(szTarget));
				memset(szReserved,0,sizeof(szReserved));
			}
			void Reset()
			{
				memset(szCmd,0,sizeof(szCmd));
				memset(szTarget,0,sizeof(szTarget));
				memset(szReserved,0,sizeof(szReserved));
			}
		};
		bool	CheckIsThereANewVersion();
		void	UpdateToLatestRelease();
		void	GetUpdateList(char *szBuffer);
	private:
		char	m_szVersionConfig[64];
		char	m_szDownLoadUrlBase[64];
		char	m_szUpdateList[64];
		char	m_szCachePath[64];
		int		m_nUpdaterVersion;
	};
}
