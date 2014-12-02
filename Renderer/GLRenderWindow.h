#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif

#include "GLDependences.h"
#include "GLShaderProgram.h"

namespace Van
{
	struct	VanCore_EXPORT	GLDrawCall
	{
		GLShaderProgram			*m_pShader;
		GLRenderMeta			*m_pRenderMeta;
		GLuint					m_uiVAO;
		int						m_nCount;
		GLDrawCall():m_pRenderMeta(NULL),m_pShader(NULL),m_uiVAO(0),m_nCount(0)
		{

		}
		void	Reset()
		{
			m_pRenderMeta=NULL;
			m_pShader=NULL;
			m_uiVAO=0;
			m_nCount=0;
		}
	};

	class VanCore_EXPORT	GLRenderWindow
	{
	public:
		HGLRC						m_hMainRC;
		int							m_uiWidth;
		int							m_uiHeight;
		GLint						m_nGLVersion;
		vector<GLDrawCall>			m_RenderQueue;
	public:
		bool						CreateRendererViaDevice(HWND hWnd,HDC hDC,unsigned int uiWidth,unsigned int uiHeight);
		void						AddOneRenderMeta(GLDrawCall &draw);
		void						RenderOneFrame();
		void						SetUpPixelFormat(const HDC *hDC);
		void						SetDefaultRenderState();
		void						ResizeRendererWindow(int iwidth,int iheight);
		void						SetViewport(int iX,int iY,int iWidth,int iHeight);
		void						GetFrustum(float **frustum);
	private:
		void						GetLocalGLInfo();
	};
}