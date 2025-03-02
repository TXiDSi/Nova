#include <Nova.h>

#include "Nova/Platform/Opengl/OpenGLShader.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//临时学习加入的库-------
#include <glad/glad.h>
#include <vector>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//---------------------

//临时构建的类或结构体（测试用 总结后转入Nova核心）-----
unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false) {
    // 拼接完整路径
    std::string fullPath = directory + "/" + path;

    // 设置 stb_image 在加载时翻转图像
    stbi_set_flip_vertically_on_load(true);

    // 生成纹理对象
    unsigned int textureID;
    glGenTextures(1, &textureID);

    // 加载图像数据
    int width, height, nrComponents;
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        // 确定图像格式
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        // 绑定纹理
        glBindTexture(GL_TEXTURE_2D, textureID);

        // 上传纹理数据
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // 设置纹理参数
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 释放图像数据
        stbi_image_free(data);
    }
    else {
        std::cerr << "Failed to load texture: " << fullPath << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    /*网格数据*/
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
public:
    /*函数*/
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }
    void Draw(Nova::Shader& shader)
    {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            // 获取纹理序号
            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++);

            shader.SetInt("material."+name+number, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh()
    {
        static int count = 0;
        NOVA_CORE_INFO("Mesh {0}", count++);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

        glBindVertexArray(0);
    }
};

class Model
{
public:
    Model(const std::string& path)
    {
        loadModel(path);
    }
    void Draw(Nova::Shader& shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }
private:
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            NOVA_CORE_ASSERT(false, "ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);

    }
    void processNode(aiNode* node, const aiScene* scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
    {
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;
            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoord = vec;
            }
            else
                vertex.texCoord = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // return a mesh object created from the extracted mesh data
        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
        }
        return textures;
    }

};

//------------------------------------------------

namespace Nova
{
    class NovaEditorLayer : public Nova::Layer
    {
    public:
        NovaEditorLayer()
            : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
        {

        }

        void OnAttach() override
        {
            //测试初始化-------
            RenderTestInit();
            //----------------
        }

        void OnUpdate(Nova::Timestep ts) override
        {
            Nova::Renderer::BeginScene(m_Camera);
            Nova::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Nova::RenderCommand::Clear();

            //测试渲染区间------
            RenderTestObject();
            //----------------

            Nova::Renderer::EndScene();
        }

        virtual void OnImGuiRender() override
        {
            static bool show = true;
            ShowViewPortWindow();
            TestImguiWindow();
        }

        void OnEvent(Nova::Event& event) override
        {

        }
    private:

        Nova::OrthographicCamera m_Camera;

    private:
        //void ShowDockSpace(bool* p_open)
        //{
        //    static bool opt_fullscreen_persistant = true;
        //    static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
        //    bool opt_fullscreen = opt_fullscreen_persistant;
        //    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        //    // because it would be confusing to have two docking targets within each others.
        //    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        //    if (opt_fullscreen)
        //    {
        //        ImGuiViewport* viewport = ImGui::GetMainViewport();
        //        ImGui::SetNextWindowPos(viewport->Pos);
        //        ImGui::SetNextWindowSize(viewport->Size);
        //        ImGui::SetNextWindowViewport(viewport->ID);
        //        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        //        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        //        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        //        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        //    }
        //    // When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        //    if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
        //        window_flags |= ImGuiWindowFlags_NoBackground;
        //    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        //    ImGui::Begin("DockSpace Demo", p_open, window_flags);
        //    ImGui::PopStyleVar();
        //    if (opt_fullscreen)
        //        ImGui::PopStyleVar(2);
        //    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        //    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
        //    if (ImGui::BeginMenuBar())
        //    {
        //        if (ImGui::BeginMenu("Docking"))
        //        {
        //            // Disabling fullscreen would allow the window to be moved to the front of other windows, 
        //            // which we can't undo at the moment without finer window depth/z control.
        //            //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
        //            if (ImGui::MenuItem("Close DockSpace", NULL, false, p_open != NULL))
        //                *p_open = false;
        //            ImGui::EndMenu();
        //        }
        //        ImGui::EndMenuBar();
        //    }
        //    ImGui::End();
        //}
        void ShowViewPortWindow()
        {
            
        }


        //----------------测试代码区------------------
        //准备数据
        // 正方体模型空间顶点数据
        float vertices[3 * 8] = {
            -0.5f, -0.5f, -0.5f,  // 顶点 0
             0.5f, -0.5f, -0.5f,  // 顶点 1
             0.5f,  0.5f, -0.5f,  // 顶点 2
            -0.5f,  0.5f, -0.5f,  // 顶点 3
            -0.5f, -0.5f,  0.5f,  // 顶点 4
             0.5f, -0.5f,  0.5f,  // 顶点 5
             0.5f,  0.5f,  0.5f,  // 顶点 6
            -0.5f,  0.5f,  0.5f   // 顶点 7
        };

        // 正方体索引数据 (每三个索引为一组三角形，组成一个面的两个三角形)
        unsigned int indices[36] = {
            // 前面
            0, 1, 2, 0, 2, 3,
            // 后面
            4, 5, 6, 4, 6, 7,
            // 左面
            0, 3, 7, 0, 7, 4,
            // 右面
            1, 2, 6, 1, 6, 5,
            // 上面
            3, 2, 6, 3, 6, 7,
            // 下面
            0, 1, 5, 0, 5, 4
        };
        const char* vertexSrc =
            R"(
                #version 330 core
                layout (location = 0) in vec3 aPos;
                layout (location = 1) in vec3 aNormal;
                layout (location = 2) in vec2 aTexCoords;

                out vec2 TexCoords;

                uniform mat4 transform;
                uniform mat4 view;
                uniform mat4 projection;

                void main()
                {
                    TexCoords = aTexCoords;
                    vec4 pos = vec4(aPos, 1.0);
                    gl_Position = projection * view * transform * pos;
                }
            )";
        const char* fragmentSrc =
            R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}
            )";
        Transform cubeTransform;
        Camera mainCamera;

        unsigned int vbo;
        unsigned int vao;
        unsigned int ebo;
        Shader* shader;

        Model testModel = Model("E:/Nova/Models/backpack/backpack.obj");

        void RenderTestInit()
        {
            glEnable(GL_DEPTH_TEST);

            glGenVertexArrays(1, &vao);         //创建顶点数组对象   
            glBindVertexArray(vao);             //绑定顶点数组对象->开始记录顶点对象信息

            glGenBuffers(1, &vbo);              //创建顶点缓冲区                              
            glBindBuffer(GL_ARRAY_BUFFER, vbo); //绑定顶点缓冲区
                                                //绑定顶点缓冲区数据
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                                                //链接顶点属性
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);       //启用顶点属性
           
            glGenBuffers(1, &ebo);              //创建索引缓冲区
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
           
            glBindVertexArray(0);               //解绑顶点数组对象->记录结束

            // 创建着色器
            shader = Shader::Create(vertexSrc, fragmentSrc);
            
            //设置正方体位置
            cubeTransform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

            //设置相机基础位置
            mainCamera.transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


        }
        void RenderTestObject()
        {   
            shader->SetMat4("transform", cubeTransform.GetTransformMatrix());
            shader->SetMat4("view", mainCamera.GetViewMatrix());
            shader->SetMat4("projection", mainCamera.GetProjectionMatrix());
            shader->Bind();
            //glBindVertexArray(vao);
            //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

            testModel.Draw(*shader);
        }

        void TestImguiWindow()
        {
            ImGui::Begin("Cube");
            ImGui::DragFloat3("Position", glm::value_ptr(cubeTransform.position), 0.01f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(cubeTransform.eulerAngle), 0.01f);
            ImGui::DragFloat3("Scale", glm::value_ptr(cubeTransform.scale), 0.01f);
            ImGui::End();

            ImGui::Begin("Camera");
            ImGui::DragFloat3("Position", glm::value_ptr(mainCamera.transform.position), 0.01f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(mainCamera.transform.eulerAngle), 0.01f);
            ImGui::End();
        }


        //------------------------------------------
    };

    class NovaEditor : public Nova::Application
    {
    public:
        NovaEditor()
        {
            PushLayer(new NovaEditorLayer());
        }

        ~NovaEditor()
        {

        }

    };

    Nova::Application* Nova::CreateApplication()
    {
        return new NovaEditor();
    }
}






