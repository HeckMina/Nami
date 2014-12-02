#define VanCore_EXPORT	__declspec(dllexport)
#include "Mesh.h"
#include "Log.h"

namespace	Van
{
	Mesh::Mesh()
	{

	}
	void	Mesh::Init()
	{
		float diamond[] = {
			-0.8f, -0.8f, 0.0f,
			1.0f, -0.8f, 0.0f,  
			0.0f,  1.0f, 0.0f ,
		};  
		float colors[] = {
			1.0f,  0.0f,  0.0f  ,
			0.0f,  1.0f,  0.0f,
			0.0f,  0.0f,  1.0f 
		};
		unsigned int vbo[3];
		/* Allocate and assign a Vertex Array Object to our handle */
		glGenVertexArrays(1, &m_nHardwareID);
		/* Bind our Vertex Array Object as the current used object */
		glBindVertexArray(m_nHardwareID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		/* Allocate and assign two Vertex Buffer Objects to our handle */
		glGenBuffers(3, vbo);
		/* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		/* Copy the vertex data from diamond to our buffer */
		/* 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values */
		glBufferData(GL_ARRAY_BUFFER,9 * sizeof(float), diamond, GL_STATIC_DRAW);
		/* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		/* Enable attribute index 0 as being used */
		/* Bind our second VBO as being the active buffer and storing vertex attributes (colors) */
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		/* Copy the color data from colors to our buffer */
		/* 12 * sizeof(GLfloat) is the size of the colors array, since it contains 12 GLfloat values */
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);
		/* Specify that our color data is going into attribute index 1, and contains three floats per vertex */
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		/* Enable attribute index 1 as being used */
		glBindBuffer(GL_INDEX_ARRAY, vbo[2]);
		/* Copy the color data from colors to our buffer */
		/* 12 * sizeof(GLfloat) is the size of the colors array, since it contains 12 GLfloat values */
		int		index[]={0,1,2};
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(int), index, GL_STATIC_DRAW);
		/* Specify that our color data is going into attribute index 1, and contains three floats per vertex */
		glVertexAttribPointer(2, 3, GL_INT, GL_FALSE, 0, 0);
		glBindBufferARB(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
	}

	void	Mesh::InitFromFBXFile(char *pFileName)
	{
		/*
		FBX		fbx;
		fbx.Init(pFileName);
		GLVAO	*pGLVAO=(GLVAO*)fbx.GetFBXMeshInfo();
		Log::DebugLog.Print("vertex count is %d",pGLVAO->nVertexCount);
		m_nHardwareID=GLResource::CreateGLVAO(pGLVAO);
		Log::DebugLog.Print("hardware id is %d",m_nHardwareID);*/
	}
}