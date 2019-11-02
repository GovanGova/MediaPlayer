#include "Mesh.h"
#include <algorithm>

Mesh::Mesh(shared_ptr<screenManager> screenMng) : m_screenMng(screenMng)
{
	m_bNormal = false;
	m_bIndex = false;
}

void Mesh::processMeshData(const aiMesh *mesh)
{
	m_bTexcordinate = mesh->mTextureCoords[0] != nullptr ? true : false;
	m_bNormal = mesh->mNormals != nullptr ? true : false;
	m_bIndex = true;
	m_materialId = mesh->mMaterialIndex;

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		m_vertex.push_back(mesh->mVertices[i].x);
		m_vertex.push_back(mesh->mVertices[i].y);
		m_vertex.push_back(mesh->mVertices[i].z);

		if (m_bNormal)
		{
			m_normal.push_back(mesh->mNormals[i].x);
			m_normal.push_back(mesh->mNormals[i].y);
			m_normal.push_back(mesh->mNormals[i].z);
		}
		if (m_bTexcordinate)
		{
			m_texcord.push_back(mesh->mTextureCoords[0][i].x);
			m_texcord.push_back(mesh->mTextureCoords[0][i].y);
			m_texcord.push_back(mesh->mTextureCoords[0][i].y);
		}
	}

	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		auto &face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for_each(face.mIndices, face.mIndices + face.mNumIndices, [&](int elem) {
			m_indices.push_back(elem);
		});
	}

	allocate_buffer();
	setvertexPointer();
}
void Mesh::allocate_buffer()
{
	//Vertex array
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//Vertex buffer
	glGenBuffers(1, &m_vBuf);
	glBindBuffer(GL_ARRAY_BUFFER, m_vBuf);
	glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(float), m_vertex.data(), GL_DYNAMIC_DRAW);

	//Texture buffer
	if (m_bTexcordinate == true)
	{
		glGenBuffers(1, &m_tBuf);
		glBindBuffer(GL_ARRAY_BUFFER, m_tBuf);
		glBufferData(GL_ARRAY_BUFFER, m_texcord.size() * sizeof(float), m_texcord.data(), GL_DYNAMIC_DRAW);
	}

	if (m_bNormal == true)
	{
		glGenBuffers(1, &m_nBuf);
		glBindBuffer(GL_ARRAY_BUFFER, m_nBuf);
		glBufferData(GL_ARRAY_BUFFER, m_normal.size() * sizeof(float), m_normal.data(), GL_DYNAMIC_DRAW);
	}
	if (m_bIndex == true)
	{
		glGenBuffers(1, &m_iBuf);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuf);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(int), m_indices.data(), GL_DYNAMIC_DRAW);
	}

	glBindVertexArray(0);
}
void Mesh::setvertexPointer()
{
	glBindVertexArray(m_vao);

	   glBindBuffer(GL_ARRAY_BUFFER, m_vBuf);
    GLuint vertexLoc = glGetAttribLocation(m_screenMng->textureProgram, "vVertex");
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    


	if (m_bTexcordinate == true)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_tBuf);
    GLuint texCoorLoc = glGetAttribLocation(m_screenMng->textureProgram, "vTexture");
    glEnableVertexAttribArray(texCoorLoc);
    glVertexAttribPointer(texCoorLoc, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	if (m_bNormal == true)
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_nBuf);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glBindVertexArray(0);
}
void Mesh::draw()
{
	glBindVertexArray(m_vao);
	if (m_bIndex == true)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuf);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, (m_vertex.size() / 3));
	}
	glBindVertexArray(0);
}