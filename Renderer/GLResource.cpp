#define  VanCore_EXPORT __declspec(dllexport)
#include "GLResource.h"
#include "Log.h"

namespace Van
{

	GLuint	GLResource::CreateGLVAO(GLVAO *pGLVAO)
	{
		GLuint	vao;
		if (NULL==pGLVAO->pVertext)
		{
			return 0;
		}
		GLuint	vbo;
		unsigned int i=0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(i);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,pGLVAO->nVertexCount*3* sizeof(float),pGLVAO->pVertext, GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		i++;
		glEnableVertexAttribArray(i);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,pGLVAO->nNormalCount*3* sizeof(float),pGLVAO->pNormal, GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBufferARB(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
		return vao;
	}
	GLuint GLResource::CreateGLVAO(GLGenericVertex *pVertex,
		GLGenericVertex *pNormal,
		GLGenericVertex *pTexCoord,
		GLGenericVertex *pIndex)
	{
		if (NULL==pVertex||NULL==pNormal||NULL==pTexCoord||NULL==pIndex)
		{
//			Van::Log::ErrLog.Print("%s:%d GLResource::CreateGLVAO fail pVertex=%d,\
//								   pNormal=%d,pTexCoord=%d,pIndex=%d!",__FILE__,__LINE__,pVertex,pNormal,pTexCoord,pIndex);
			return 0;
		}
		GLuint		vao=0;
		GLuint		vbo=0;
		GLuint		i=0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		//vertex
		glEnableVertexAttribArray(i);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,pVertex->nVertexCount*3* sizeof(float),pVertex->pData, GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//normal
		i++;
		glEnableVertexAttribArray(i);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,pNormal->nVertexCount*3* sizeof(float),pNormal->pData, GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//texcoord
		i++;
		glEnableVertexAttribArray(i);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,pTexCoord->nVertexCount*2* sizeof(float),pTexCoord->pData, GL_STATIC_DRAW);
		glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//index
		i++;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,pIndex->nVertexCount*sizeof(GLuint),pIndex->pData, GL_STATIC_DRAW);

		glBindBufferARB(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
		return vao;
	}
}