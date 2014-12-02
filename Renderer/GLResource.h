#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT __declspec(dllimport)
#endif

#include "GLDependences.h"

namespace Van
{
	struct	VanCore_EXPORT GLGenericVertex
	{
		float	*pData;
		int		nVertexCount;
		GLGenericVertex():pData(NULL),nVertexCount(0)
		{

		}
		~GLGenericVertex()
		{
			delete [] pData;
		}
	};

	struct	VanCore_EXPORT	GLTexture
	{

	};

	struct	VanCore_EXPORT GLVAO
	{
		float	*pVertext;
		float	*pNormal;
		float	*pTextureCoords;
		float	*pColor;
		int		nVertexCount;
		int		nNormalCount;
		int		nTextureCoordsCount;
		int		nColorCount;
		GLVAO():pVertext(NULL),pNormal(NULL),pTextureCoords(NULL),pColor(NULL),
			nVertexCount(0),nNormalCount(0),nTextureCoordsCount(0),nColorCount(0)
		{

		}
	};
	class	VanCore_EXPORT	GLResource
	{
	public:
		static	GLuint	CreateGLVAO(GLVAO *pGLVAO=NULL);
		static	GLuint	CreateGLVAO(GLGenericVertex *pVertex,
									GLGenericVertex *pNormal,
									GLGenericVertex *pTexCoord,
									GLGenericVertex *pIndex);
	};
}