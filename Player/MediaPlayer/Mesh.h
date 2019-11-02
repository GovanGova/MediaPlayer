//
//
#pragma once

#include "Base.h"
#include <vector>
#include "assimp/mesh.h"
#include "ScreenManager.h"
using namespace std;

class Mesh
{

public:

	Mesh(shared_ptr<screenManager> screenMng);
	void processMeshData(const aiMesh *mesh);

	//
	// This function is used to allocate the vertex, texture and normal buffer to store the corresponding information to
	// draw the loaded .obj file.
	//
	void allocate_buffer();

	//
	//This function will set the pointer to pervertex attribute
	//
	void setvertexPointer();

	//
	//Function used to draw the loaded .obj file.
	//
	void draw();

private:
	vector<float> m_vertex;
	vector<float> m_texcord;
	vector<float> m_normal;
	vector<int> m_indices;

	GLuint m_vBuf, m_tBuf, m_nBuf, m_iBuf;
	GLuint m_vao;
	int m_materialId{-1};

	bool m_bTexcordinate, m_bNormal, m_bIndex;
	shared_ptr<screenManager> m_screenMng;
};