#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include<stdlib.h>
#include<windows.h>
#include<direct.h>
using namespace std;
#include "RenderWindow.h"
#include "Log.h"

namespace Van
{
	class	VanCore_EXPORT	Application
	{
	private:
		static	Application	*	m_pStatic;
	protected:
		Application();
		~Application();
		RenderWindow		*m_pRenderWindow;
	public:
		static	Application *	GetInstancePtr();
		string					GetRuntimePlatform();
		bool					AddEnviroment(const char *path);
		void					Quit();
		void					CreateRenderWindow(void *pData);
		RenderWindow			*GetRenderWindow();
	};
}