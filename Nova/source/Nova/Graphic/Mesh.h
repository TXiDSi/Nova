#pragma once
#include "vector"
#include "Nova/Renderer/Shader.h"
#include "Nova/Renderer/Buffer.h"
#include "Nova/Renderer/VertexArray.h"
#include "Nova/Graphic/Vertex.h"

#include "glad/glad.h"

namespace Nova
{
    class Mesh
    {
    public:
        /*网格数据*/
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    public:
        /*函数*/
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        void Bind() const;
    private:
        void setupMesh();      
    private:
        std::shared_ptr<VertexArray>    m_vao;
        std::shared_ptr<VertexBuffer>   m_vbo;
        std::shared_ptr<IndexBuffer>    m_ebo;
    };
}

