#pragma once

#include "Nova/Graphic/Mesh.h"
#include "Nova/Renderer/Shader.h"
#include <assimp/scene.h>
namespace Nova
{
    class Model
    {
    public:
        Model(const std::string& path);
        std::vector<std::shared_ptr<Mesh>> meshes;
    private:   
        std::string directory;
        void loadModel(const std::string& path);     
        void processNode(aiNode* node, const aiScene* scene);
        std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);   
    };
}


