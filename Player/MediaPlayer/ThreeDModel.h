//
// Created by G on 5/29/2018.
//

#pragma once
#include "Element.h"
#include "Mesh.h"
#include "map"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class ThreeDModel : public Element
{
public:
    ThreeDModel(shared_ptr<screenManager> screenMng);

    void tick(float tSecs) override;
    void render() override;
    void unload() override;
    void setFilename(string filename);

    ~ThreeDModel();

private:
    class MeshData
    {
    public:
        shared_ptr<Mesh> m_mesh;
        int m_diffuseTexId{-1};
        int m_specTexId{-1};
        int m_ambientTexId{-1};
    };

    
    void loadMeshData(const aiScene *scene);
    void loadMaterialData(shared_ptr<MeshData> meshData, aiMaterial *material);

    vector<shared_ptr<MeshData>> m_meshes;
    map<string, int> textureLoaded;
    string m_filename;
};