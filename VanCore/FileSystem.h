#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include <iostream>
using namespace  std;
namespace Van
{
	class VanCore_EXPORT FileSystem
	{
	private:
		static	FileSystem	*	m_pStatic;
		char					m_szShaderDir[64];
	protected:
		FileSystem();
		~FileSystem();
	public:
		static	FileSystem	*	GetSingletonPtr();
	public:
		char*	ReadShaderSourceFile(char *pShaderName);
		int		WriteTextFile(char *szFileName, char *pSrc);
		void	Release();
	};
}