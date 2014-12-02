#define VanCore_EXPORT _declspec(dllexport)
#include "Directory.h"
#include "Log.h"
#pragma warning(disable:4996)

namespace Van
{
	bool	Directory::Exsit(string strPath)
	{
		bool bRet=false;
		HANDLE				hHandle=INVALID_HANDLE_VALUE;
		WIN32_FIND_DATAA	FindFileData;
		memset(&FindFileData,0,sizeof(FindFileData));
		hHandle = FindFirstFileA(strPath.c_str(), &FindFileData);
		if (INVALID_HANDLE_VALUE!=hHandle)
		{
			if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY )
			{
				bRet=true;
			}
		}
		FindClose(hHandle);
		return bRet;
	}

	list<string> Directory::GetAllFilesInThisDirectory(string strPath)
	{
		list<string>		lFilesRet;
		HANDLE				hHandle=INVALID_HANDLE_VALUE;
		WIN32_FIND_DATAA	FindFileData;
		memset(&FindFileData,0,sizeof(FindFileData));
		string				strDir=strPath+"/*";
		hHandle = FindFirstFileA(strDir.c_str(), &FindFileData);
		if (INVALID_HANDLE_VALUE==hHandle)
		{
			Van::Log::ErrLog.Print("GetAllFilesInThisDir fail,Invalid file handle. Error is %u \n", GetLastError());
			FindClose(hHandle);
			return lFilesRet;
		}
		else
		{
			if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY )
			{
				string strFilePath=strPath+"/"+FindFileData.cFileName;
				lFilesRet.push_back(strFilePath);
			}
			else if(FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY
				&& strcmp(FindFileData.cFileName, ".") != 0
				&& strcmp(FindFileData.cFileName, "..") != 0)
			{
				string strDirPath=strPath+"/"+FindFileData.cFileName;
				list<string> lFiles=GetAllFilesInThisDirectory(strDirPath);
				for (list<string>::iterator iter=lFiles.begin();iter!=lFiles.end();iter++)
				{
					lFilesRet.push_back(*iter);
				}
			}
			while (FindNextFileA(hHandle, &FindFileData) != 0)
			{
				if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				{
					string strFilePath=strPath+"/"+FindFileData.cFileName;
					lFilesRet.push_back(strFilePath);
				}
				else if(FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY
					&& strcmp(FindFileData.cFileName, ".") != 0
					&& strcmp(FindFileData.cFileName, "..") != 0)
				{
					string strDirPath=strPath+"/"+FindFileData.cFileName;
					list<string> lFiles=GetAllFilesInThisDirectory(strDirPath);
					for (list<string>::iterator iter=lFiles.begin();iter!=lFiles.end();iter++)
					{
						lFilesRet.push_back(*iter);
					}
				}
			}
			DWORD	dwError=GetLastError();
			FindClose(hHandle);
			if ( dwError!= ERROR_NO_MORE_FILES)
			{
				Van::Log::ErrLog.Print("GetAllFilesInThisDir fail,Invalid file handle. Error is %u \n",dwError);
				return lFilesRet;
			}
		}
		return lFilesRet;
	}
}