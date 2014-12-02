#define VanCore_EXPORT	__declspec(dllexport)

#include "GLShaderProgram.h"

namespace	Van
{
	void	GLShaderProgram::SetShader(const char *pVertex,const char *pFrag)
	{
		m_hVertexShader=glCreateShader(GL_VERTEX_SHADER);
		if (0==m_hVertexShader)
		{
			printf("create vertex shader fail");
			return ;
		}
		glShaderSource(m_hVertexShader,1,&pVertex,NULL);
		glCompileShader(m_hVertexShader);
 
		GLint nResult;
		glGetShaderiv(m_hVertexShader,GL_COMPILE_STATUS,&nResult);  
		if (GL_FALSE == nResult)  
		{  
			GLint logLen;  
			glGetShaderiv(m_hVertexShader,GL_INFO_LOG_LENGTH,&logLen);  
			if (logLen > 0)  
			{  
				char *log = (char *)malloc(logLen);  
				GLsizei written;  
				glGetShaderInfoLog(m_hVertexShader,logLen,&written,log);  
				printf("vertex shader compile log : %s",log);  
				free(log);
			}  
		}  
		
		m_hFragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
		if (0==m_hFragmentShader)
		{
			printf("create fragment shader fail");
			return ;
		}
		glShaderSource(m_hFragmentShader,1,&pFrag,NULL);
		glCompileShader(m_hFragmentShader);

		glGetShaderiv(m_hFragmentShader,GL_COMPILE_STATUS,&nResult);  
		if (GL_FALSE == nResult)  
		{  
			GLint logLen;  
			glGetShaderiv(m_hFragmentShader,GL_INFO_LOG_LENGTH,&logLen);  
			if (logLen > 0)  
			{  
				char *log = (char *)malloc(logLen);  
				GLsizei written;  
				glGetShaderInfoLog(m_hFragmentShader,logLen,&written,log);  
				printf("fragment shader compile log : %s",log);  
				free(log);
			}  
		}  
		m_hProgram=glCreateProgram();
		if(0==m_hProgram)
		{
			printf("glCreateProgram fail! %s:%d\n",__FILE__,__LINE__);
			return ;
		}
		glAttachShader(m_hProgram,m_hVertexShader);
		glAttachShader(m_hProgram,m_hFragmentShader);

		glBindAttribLocation(m_hProgram,0,"VertexPosition");
		glBindAttribLocation(m_hProgram,1,"VertexColor");
		glBindFragDataLocation(m_hProgram,0,"X");
		
		glLinkProgram(m_hProgram);
		glGetProgramiv(m_hProgram,GL_LINK_STATUS,&nResult);
		if (GL_FALSE==nResult)
		{
			printf("fail to link to program!\n");
			GLint logLen;
			glGetProgramiv(m_hProgram,GL_INFO_LOG_LENGTH,&logLen);
			if (logLen>0)
			{
				char *log=new char[logLen];
				GLsizei written;
				glGetShaderInfoLog(m_hProgram,logLen,&written,log);
				printf("%s\n",log);
				delete log;
				log=NULL;
			}
		}
	}

	void	GLShaderProgram::AddAttribute(string strAttributeName,glm::mat4 &matrix)
	{
		int nLocation = glGetUniformLocation(m_hProgram, strAttributeName.c_str());
		if (m_UniformMatrixMap.find(nLocation)==m_UniformMatrixMap.end())
		{
			m_UniformMatrixMap.insert(pair<int,glm::mat4>(nLocation,matrix));
		}
	}

	void	GLShaderProgram::SetAttribute(string strAttributeName,glm::mat4 &matrix)
	{
		int nLocation = glGetUniformLocation(m_hProgram, strAttributeName.c_str());
		if (m_UniformMatrixMap.find(nLocation)!=m_UniformMatrixMap.end())
		{
			m_UniformMatrixMap[nLocation]=matrix;
		}
	}

	void	GLShaderProgram::SetAttritute(string strAttributeName,float fParam)
	{

	}

	void	GLShaderProgram::MakeAsCurrentShader()
	{
		glUseProgram(m_hProgram);
		map<int,glm::mat4>::iterator iter=m_UniformMatrixMap.begin();
		while(iter!=m_UniformMatrixMap.end())
		{
			glUniformMatrix4fv(iter->first, 1, GL_FALSE,&(iter->second)[0][0]);
			iter++;
		}
	}

	GLShaderProgram::~GLShaderProgram()
	{
		/*glUseProgram(0);
		glDetachShader(m_hProgram,m_hVertexShader);
		printf("Detach vertex shader\n");
		//glDeleteShader(m_hVertexShader);
		printf("Delete vertex shader\n");
		glDetachShader(m_hProgram,m_hFragmentShader);
		printf("Detach frag shader\n");
		//glDeleteShader(m_hFragmentShader);
		printf("Delete frag shader\n");
		glDeleteProgram(m_hProgram);
		printf("Delete program \n");*/
	}
}