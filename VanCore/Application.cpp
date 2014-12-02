#define VanCore_EXPORT _declspec(dllexport)
#include "Application.h"

namespace Van
{
	Application *Application::m_pStatic=NULL;
	Application *Application::GetInstancePtr()
	{
		if(NULL==m_pStatic)
		{
			m_pStatic=new Application();
		}
		return m_pStatic;
	}

	RenderWindow	*Application::GetRenderWindow()
	{
		if (NULL==m_pRenderWindow)
		{
			Van::Log::DebugLog.Print("Init RenderWindow Start--->!");
			m_pRenderWindow=new RenderWindow();
			HINSTANCE hInstance=GetModuleHandleA(NULL);
			m_pRenderWindow->Init(&hInstance);
		}
		return m_pRenderWindow;
	}

	void	Application::CreateRenderWindow(void *pData)
	{
		if (NULL==m_pRenderWindow)
		{
			m_pRenderWindow=new RenderWindow();
			m_pRenderWindow->Init(pData);
		}
	}

	string	Application::GetRuntimePlatform()
	{
		string strPlatform="unkown";
#ifdef WIN32
		strPlatform="Windows";
#else
		strPlatform="unkown";
#endif
		return strPlatform;
	}

	bool	Application::AddEnviroment(const char *path)
	{
		bool bRet=false;
		char *buffer;
		string str="PATH=";
		buffer = getenv( "PATH" );

		if( buffer != NULL )
		{
			str+=buffer;
			bRet=true;
		}
		if (str.c_str()[str.size()-1] == ';')
		{
			str+=path;
		}
		else
		{
			str+=";";
			str+=path;
		}
		_putenv( str.c_str() );
		return bRet;
	}

	void Application::Quit()
	{
		
		m_pRenderWindow->Quit();
	}

	Application::Application():m_pRenderWindow(NULL)
	{
		
	}

	Application::~Application()
	{

	}
}