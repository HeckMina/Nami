#define VanCore_EXPORT  _declspec(dllexport)
#include "GLRenderWindow.h"

namespace Van
{
	bool GLRenderWindow::CreateRendererViaDevice(HWND hWnd,HDC hDC,unsigned int uiWidth,unsigned int uiHeight)
	{
		m_uiWidth=uiWidth;
		m_uiHeight=uiHeight;
		HGLRC	tempOpenGLContext;
		SetUpPixelFormat(&hDC);
		tempOpenGLContext=wglCreateContext(hDC);
		wglMakeCurrent(hDC,tempOpenGLContext);
		GLenum ret=glewInit();
		if (GLEW_OK!=ret)
		{
			printf("glew init fail ! %s %s:%d",glewGetErrorString(ret),__FILE__,__LINE__);
			return false;
		}
		int attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3, // Set the MAJOR version of OpenGL to 3
			WGL_CONTEXT_MINOR_VERSION_ARB, 2, // Set the MINOR version of OpenGL to 2
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
			0
		};
		if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available
			m_hMainRC = wglCreateContextAttribsARB(hDC, NULL, attributes); // Create and OpenGL 3.x context based on the given attributes
			wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
			wglDeleteContext(tempOpenGLContext); // Delete the temporary OpenGL 2.1 context
			wglMakeCurrent(hDC, m_hMainRC); // Make our OpenGL 3.0 context current
		}
		else
		{
			m_hMainRC=tempOpenGLContext;
		}
		SetDefaultRenderState();
		GetLocalGLInfo();
		return true;
	}

	void	GLRenderWindow::GetLocalGLInfo()
	{
		printf("========local opengl renderer info:========begin\n");
		const GLubyte	*renderer=glGetString(GL_RENDERER);
		const GLubyte	*vendor=glGetString(GL_VENDOR);
		const GLubyte	*version=glGetString(GL_VERSION);
		const GLubyte	*glslVersion=glGetString(GL_SHADING_LANGUAGE_VERSION);
		GLint	minor;
		glGetIntegerv(GL_MAJOR_VERSION,&m_nGLVersion);
		glGetIntegerv(GL_MINOR_VERSION,&minor);
		printf("GL vendor : %s \n",vendor);
		printf("GL renderer : %s \n",renderer);
		printf("GL version : %s \n",version);
		printf("GL glslVersion : %s \n",glslVersion);
		printf("GL major : %d.%d ",m_nGLVersion,minor);
		GLint	nExtensionCounts=1;
		glGetIntegerv(GL_NUM_EXTENSIONS,&nExtensionCounts);
		for (int i=0;i<nExtensionCounts;i++)
		{
			printf("%s \n",glGetStringi(GL_EXTENSIONS,i));
		}
		printf("max vertex attribute is :%d",GL_MAX_VERTEX_ATTRIBS);
		printf("========local opengl renderer info:========end\n");
	}

	void	GLRenderWindow::AddOneRenderMeta(GLDrawCall &draw)
	{
		m_RenderQueue.push_back(draw);
	}
	
	void	GLRenderWindow::RenderOneFrame()
	{
		glViewport(0,0,m_uiWidth,m_uiHeight);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BITS);

		while(!m_RenderQueue.empty())
		{
			glBindVertexArray(m_RenderQueue.back().m_uiVAO);
			//glDrawArrays(GL_TRIANGLES, 0,m_RenderQueue.back().m_nCount);
			glDrawElements(GL_TRIANGLES,3,GL_INT,0);
			glBindVertexArray(0);
			m_RenderQueue.pop_back();
		}
		glFlush();
	}
	void	GLRenderWindow::SetViewport(int iX,int iY,int iWidth,int iHeight)
	{
		glViewport(iX,iY,iWidth,iHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		double	aspectRatio=(double)iWidth/(double)iHeight;
		const double DEG2RAD = 3.14159265 / 180;
		double tangent = tan(30.0f/2 * DEG2RAD);   // tangent of half fovY    
		double ly = 1.0 * tangent;				  // half height of near plane    
		double lx = ly* aspectRatio;      // half width of near plane
		//这个视锥体感觉比下面那个好用，主要是这个函数能够让我更明白这视锥体是怎么算出来的。
		//还有就是在嵌入式设备上是没有glu的函数的，所以最好是把这种东西剔除出程序。
		glFrustum(-lx,lx,-ly,ly,1.0f,500.0f);
		//gluPerspective(50.0f,(GLfloat)width/(GLfloat)height,1.0f,500.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void	GLRenderWindow::ResizeRendererWindow(int iwidth,int iheight)
	{
		m_uiWidth=iwidth;
		m_uiHeight=iheight;
		glViewport(0,0,iwidth,iheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		double	aspectRatio=(double)iwidth/(double)iheight;
		const double DEG2RAD = 3.14159265 / 180;
		double tangent = tan(30.0f/2 * DEG2RAD);   // tangent of half fovY    
		double ly = 1.0 * tangent;				  // half height of near plane    
		double lx = ly* aspectRatio;      // half width of near plane
		//这个视锥体感觉比下面那个好用，主要是在做UI的时候好用
		glFrustum(-lx,lx,-ly,ly,1.0f,500.0f);
		//gluPerspective(50.0f,(GLfloat)width/(GLfloat)height,1.0f,500.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void	GLRenderWindow::SetDefaultRenderState()
	{
		glClearColor(0,0,0,1.0f);
		//m_projectionMatrix=glm::perspective(60.0f,(float)m_uiWidth/(float)m_uiHeight,0.1f,100.0f);
		//m_viewMatrix=glm::lookAt(glm::vec3(0,0,5.0),glm::vec3(0,0,0),glm::vec3(0,1,0));
		//m_viewMatrix2=glm::lookAt(glm::vec3(0,3.0,5.0),glm::vec3(0,0,0),glm::vec3(0,1,0));
		//m_modelMatrix=glm::mat4(1.0);
	}


	void	GLRenderWindow::GetFrustum(float **frustum)
	{

	}

	void	GLRenderWindow::SetUpPixelFormat(const HDC *hDC)
	{
		int pixelFormat;
		PIXELFORMATDESCRIPTOR pfd=
		{
			sizeof(PIXELFORMATDESCRIPTOR),//大小
			1,                           //版本
			PFD_SUPPORT_OPENGL|          //OpenGL窗口
			PFD_DRAW_TO_WINDOW|          //渲染窗口
			PFD_DOUBLEBUFFER|            //支持双缓冲区
			PFD_TYPE_RGBA,               //颜色类型
			32,                          //颜色深度
			0,0,0,0,0,0,				 //颜色位数（忽略）
			0,                           //没有alpha缓冲区
			0,                           //alpha字节位（忽略）
			0,                           //没有聚集缓冲区
			0,0,0,0,                     //聚集字节位（忽略）
			16,                          //深度缓冲区
			0,                           //没有模板缓冲区
			0,                           //没有辅助缓冲区
			PFD_MAIN_PLANE,              //主层次
			0,                           //保留
			0,0,0                        //没有层次，可见性，破损遮罩
		};

		pixelFormat=ChoosePixelFormat(*hDC,&pfd);//gdi32.lib
		SetPixelFormat(*hDC,pixelFormat,&pfd);//gdi32.lib
	}
}