#include "Mesh.h"
namespace Nova
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;
        setupMesh();
    }

    void Mesh::setupMesh()
    {
        m_vao = VertexArray::Create();
        m_vao->Bind();

        m_vbo = VertexBuffer::Create(&vertices[0],vertices.size()*sizeof(Vertex));
        m_ebo = IndexBuffer::Create(&indices[0], indices.size());

        m_ebo->Bind();
        m_vbo->Bind();

        m_vbo->SetPoint(0, 3, ShaderDataType::Float, false, sizeof(Vertex), 0);
        m_vbo->SetPoint(1, 3, ShaderDataType::Float, false, sizeof(Vertex), offsetof(Vertex, normal));
        m_vbo->SetPoint(2, 2, ShaderDataType::Float, false, sizeof(Vertex), offsetof(Vertex, uv));
        
        m_vao->Unbind();
    }

    void Mesh::Bind() const
    {
        m_vao->Bind();
    }
}