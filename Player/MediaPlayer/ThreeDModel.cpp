#include "ThreeDModel.h"
#include "Texture.h"

ThreeDModel::ThreeDModel(shared_ptr<screenManager> screenMng) : Element(screenMng)
{
}

void ThreeDModel::loadMaterialData(std::shared_ptr<MeshData> meshData, aiMaterial *material)
{
    auto directory = m_filename.substr(0, m_filename.find_last_of('/'));

    // Load diffuse material
    //
    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
         aiString file_name;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &file_name);
        string filename(file_name.C_Str());
        if (textureLoaded[filename])
            meshData->m_diffuseTexId = textureLoaded[filename];
        else
        {
            meshData->m_diffuseTexId = Texture::loadTextureFile(directory+'/'+filename);
            textureLoaded[filename] = meshData->m_diffuseTexId;
        }
    }

    // Load specular map
    //
    if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
    {
        aiString file_name;
        material->GetTexture(aiTextureType_SPECULAR, 0, &file_name);
        string filename(file_name.C_Str());
        if (textureLoaded[filename])
            meshData->m_specTexId = textureLoaded[filename];
        else
        {
            meshData->m_specTexId = Texture::loadTextureFile(directory+'/'+filename);
            textureLoaded[filename] = meshData->m_specTexId;
        }
    }

    // Load ambient map
    //
    if (material->GetTextureCount(aiTextureType_AMBIENT) > 0)
    {
        aiString file_name;
        material->GetTexture(aiTextureType_AMBIENT, 0, &file_name);
        string filename(file_name.C_Str());
        if (textureLoaded[filename])
            meshData->m_ambientTexId = textureLoaded[filename];
        else
        {
            meshData->m_ambientTexId = Texture::loadTextureFile(directory+'/'+filename);
            textureLoaded[filename] = meshData->m_ambientTexId;
        }
    }
}
void ThreeDModel::loadMeshData(const aiScene *scene)
{
    if (scene)
    {
        for (uint i = 0; i < scene->mNumMeshes; i++)
        {
            auto meshDat = std::shared_ptr<MeshData>(new MeshData());
            meshDat->m_mesh = std::shared_ptr<Mesh>(new Mesh(m_screenMng));
            meshDat->m_mesh->processMeshData(scene->mMeshes[i]);

            //load material
            aiMaterial *material = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
            loadMaterialData(meshDat, material);
            //Texture::loadTextureFile()
            //meshDat.m_texId = Texture::loadTextureFile(scene->mMaterials[scene->mMeshes[i]])

            m_meshes.push_back(meshDat);
        }
    }
}

void ThreeDModel::tick(float tSecs)
{
    if (!m_isReady)
    {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(m_filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
        loadMeshData(scene);
        m_isReady = true;
    }
    //Element::tick(tSecs);
}
void ThreeDModel::render()
{
    if (!m_isReady)
        return;

    glUseProgram(m_screenMng->textureProgram);
    GLuint colorLoc = glGetUniformLocation(m_screenMng->shapeProgram, "vColor");
//    glUniform4f(colorLoc, this->m_r, this->m_g, this->m_b, this->m_a);

    GLuint mvpLoc = glGetUniformLocation(m_screenMng->shapeProgram, "mvpMatrix");
    glm::mat4 rMat = glm::mat4(1.0);
    glm::mat4 tMat = glm::mat4(1.0); // m_screenMng->getModelViewMatrix();
    //glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    //mvMat = m_screenMng->getModelViewMatrix() * glm::tte(mvMat,
        
    tMat = glm::translate(tMat, glm::vec3(this->getPosX(), this->getPosY(), this->getPosZ()));
    rMat=glm::rotate(rMat, 4.5f, glm::vec3(1.0,0.0,0.0));

    auto mvMat = m_screenMng->getModelViewMatrix() *tMat*rMat;
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(m_screenMng->getProjectionMatrix()*mvMat));
    //glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(m_screenMng->getModelViewProjection()));
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (auto mesh : m_meshes)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->m_diffuseTexId);
        GLuint samplerLoc = glGetUniformLocation(m_screenMng->textureProgram, "sampler");
        glUniform1i(samplerLoc, 0);

        mesh->m_mesh->draw();
    }
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void ThreeDModel::unload()
{
    for (auto mesh : m_meshes)
    {
    }
}
void ThreeDModel::setFilename(string filename)
{
    if (m_filename != filename)
    {
        m_filename = filename;
    }
}

ThreeDModel::~ThreeDModel()
{
    unload();
}