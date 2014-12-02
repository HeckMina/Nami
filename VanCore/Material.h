#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include "VanCoreDependences.h"
#include "GLShaderProgram.h"
#include "Texture.h"

namespace Van
{
	class VanCore_EXPORT Material
	{
	public:
		enum CullType
		{
			Front,
			Back,
			Off
		};
		enum ZTestType
		{
			ZT_Less,
			ZT_Greater,
			ZT_LEqual,
			ZT_GEqual,
			ZT_Equal,
			ZT_NotEqual,
			ZT_Always
		};
		enum AlphaTestType
		{
			AT_Less,
			AT_Greater,
			AT_LEqual,
			AT_Equal,
			AT_NotEqual,
			AT_Always
		};
	public:
		bool			m_bIsZWriteOn;
		bool			m_bIsLightingOn;
		int				m_nLODLevel;
		//CullType		m_eCullType;
		//ZTestType		m_eZTestType;
		//AlphaTestType	m_eAlphaTestType;
		float			m_fAlphaTestCutoffValue;
		GLShaderProgram	m_GLShader;
		Texture			m_Texture;
		//colormask
		//color
		//diffuse color
		//ambient color
		//specular color
		//shininess number
		//emission color
		void			Init();
		void			MakeAsCurrentMat();
	};
}