#define VanCore_EXPORT _declspec(dllexport)
#include "FileSystem.h"
#pragma warning(disable:4996)

namespace Van
{
	FileSystem	*	FileSystem::m_pStatic=NULL;
	FileSystem::FileSystem()
	{
		memset(m_szShaderDir,0,sizeof(m_szShaderDir));
		memcpy(m_szShaderDir,"media/shader/",strlen("media/shader/"));
	}
	
	FileSystem::~FileSystem()
	{

	}

	FileSystem	*	FileSystem::GetSingletonPtr()
	{
		if (NULL==m_pStatic)
		{
			m_pStatic=new FileSystem();
		}
		return m_pStatic;
	}

	void	FileSystem::Release()
	{
		if (m_pStatic!=NULL)
		{
			delete m_pStatic;
		}
	}

	int		FileSystem::WriteTextFile(char *szFileName, char *pSrc)
	{
		FILE *pFile;
		int status = 0;
		if (szFileName != NULL)
		{
			pFile = fopen(szFileName,"w");
			if (pFile != NULL)
			{
				if (fwrite(pSrc,sizeof(char),strlen(pSrc),pFile) == strlen(pSrc))
					status = 1;
				fclose(pFile);
			}
		}
		return(status);
	}

	char*	FileSystem::ReadShaderSourceFile(char *pShaderName)
	{
		FILE *pFile=NULL;
		char *pData=NULL;
		int count=0;
		char szFullPath[256];
		memset(szFullPath,0,sizeof(szFullPath));
		memcpy(szFullPath,m_szShaderDir,sizeof(m_szShaderDir));
		strcat(szFullPath,pShaderName);
		if (pShaderName != NULL)
		{
			pFile = fopen(szFullPath,"rt");
			if (pFile != NULL)
			{
				fseek(pFile, 0, SEEK_END);
				count = ftell(pFile);
				rewind(pFile);
				if (count > 0)
				{
					pData = (char *)malloc(sizeof(char) * (count+1));
					count = fread(pData,sizeof(char),count,pFile);
					pData[count] = '\0';
				}
				fclose(pFile);
			}
		}
		return pData;
	}
}