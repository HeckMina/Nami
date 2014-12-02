#define VanCore_EXPORT _declspec(dllexport)
#include "Material.h"
#include "FileSystem.h"

namespace Van
{
	void	Material::Init()
	{
		char	*pVertex=FileSystem::GetSingletonPtr()->ReadShaderSourceFile("diffuse.vert");
		char	*pFrag=FileSystem::GetSingletonPtr()->ReadShaderSourceFile("diffuse.frag");
		m_GLShader.SetShader(pVertex,pFrag);
		free(pVertex);
		free(pFrag);
	}

	void	Material::MakeAsCurrentMat()
	{
		m_GLShader.MakeAsCurrentShader();
	}
}