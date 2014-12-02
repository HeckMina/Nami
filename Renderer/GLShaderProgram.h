#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT __declspec(dllimport)
#endif
#include "GLDependences.h"

namespace Van
{
	class VanCore_EXPORT	GLShaderProgram
	{
	public:
		~GLShaderProgram();
		void			SetShader(const char *pVertex,const char *pFrag);
		void			MakeAsCurrentShader();
		void			SetAttritute(string strAttributeName,float fParam);
		void			AddAttribute(string strAttributeName,glm::mat4 &matrix);
		void			SetAttribute(string strAttributeName,glm::mat4 &matrix);
	protected:
		map<int,glm::mat4>	m_UniformMatrixMap;
		map<int,float>		m_UniformFloatMap;
		GLhandleARB			m_hProgram;
		GLhandleARB			m_hVertexShader;
		GLhandleARB			m_hFragmentShader;
	private:
	};
}