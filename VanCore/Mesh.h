#pragma once
#ifdef VanCore_EXPORT
#else
#define  VanCore_EXPORT __declspec(dllimport)
#endif
#include "VanCoreDependences.h"
#include "GLResource.h"
#include "GLShaderProgram.h"

namespace	Van
{
	class	VanCore_EXPORT	Mesh
	{
	public:
		Mesh();
		void		Init();
		void		InitFromFBXFile(char *pFileName);
	public:
		float		*m_pVertex;
		float		*m_pTextureCoord;
		float		*m_pNormal;
		int			m_nVertexCount;
		float		*m_pColor;
		unsigned int m_nHardwareID;
	};
	class	VanCore_EXPORT	MeshObject
	{
	public:
		GLuint				m_uiVAOObject;
		GLShaderProgram		m_Mat;
	};
}