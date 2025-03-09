#include <Nova.h>


#include "Core/AssetsManager.h"

#include "Nova/Platform/Opengl/OpenGLShader.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace NovaEditor;

//¡Ÿ ±—ßœ∞º”»Îµƒø‚-------
#include <glad/glad.h>
#include <vector>
#include <stb_image.h>
//---------------------


namespace Nova
{
    class EditorLayer : public Nova::Layer
    {
    public:
        EditorLayer()
            : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
        {

        }

        void OnAttach() override
        {
            //≤‚ ‘≥ı ºªØ-------
            RenderTestInit();
            SceneInit();
            //----------------
        }

        void OnUpdate(Nova::Timestep ts) override
        {
            Nova::Renderer::BeginScene();
            Nova::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Nova::RenderCommand::Clear();

            //≤‚ ‘‰÷»æ«¯º‰------
            RenderTestObject();
            //----------------
            //Scene≤‚ ‘«¯º‰----
            SceneUpdate();
            //----------------

            Nova::Renderer::EndScene();
        }

        virtual void OnImGuiRender() override
        {
            ShowViewPortWindow();
            TestImguiWindow();
        }

        void OnEvent(Nova::Event& event) override
        {

        }
    private:

        Nova::OrthographicCamera m_Camera;

    private:

        void ShowViewPortWindow()
        {
            
        }


        //----------------≤‚ ‘¥˙¬Î«¯------------------
        Camera mainCamera;
        DirectionalLight light;
        std::shared_ptr<Shader> shader;
        Transform transform;

        std::shared_ptr<Model> testModel;
        std::shared_ptr<FrameBuffer> frameBuffer;

        //---------≤‚ ‘ÃÏø’∫–--------
        float skyboxVertices[3*6*6] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };
        std::shared_ptr<VertexArray> skyboxVAO;
        std::shared_ptr<VertexBuffer> skyboxVBO;
        std::shared_ptr<Shader> skyboxShader;
        std::shared_ptr<CubeMap> skyBoxTexture;
        std::vector<std::string> faces
        {
            "E:/Nova/Assets/Textures/CubeMap/skybox/right.jpg",
            "E:/Nova/Assets/Textures/CubeMap/skybox/left.jpg",
            "E:/Nova/Assets/Textures/CubeMap/skybox/top.jpg",
            "E:/Nova/Assets/Textures/CubeMap/skybox/bottom.jpg",
            "E:/Nova/Assets/Textures/CubeMap/skybox/front.jpg",
            "E:/Nova/Assets/Textures/CubeMap/skybox/back.jpg"
        };
        //---------≤‚ ‘ÃÏø’∫–--------

        void RenderTestInit()
        {     
            testModel = std::make_shared<Model>("E:/Nova/Assets/Models/Stanford/bunny_10k.obj");            
            light.color = glm::vec3(1.0f, 1.0f, 1.0f);
            light.direction = glm::vec3(0.0f, -1.0f, 0.0f);

            std::string vertexSrc = AssetsManager::GetVertexShaderSource("Shaders/Nova_Standard.glsl");
            std::string fragmentSrc = AssetsManager::GetFragmentShaderSource("Shaders/Nova_Standard.glsl");
            // ¥¥Ω®◊≈…´∆˜
            shader = Shader::Create(vertexSrc, fragmentSrc);    

            frameBuffer = FrameBuffer::Create();
            frameBuffer->SetTextureSize(1920, 1080);

            //---------≤‚ ‘ÃÏø’∫–--------
            skyboxVAO = VertexArray::Create();
            skyboxVAO->Bind();
            skyboxVBO = VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
            vertexSrc = AssetsManager::GetVertexShaderSource("Shaders/Nova_Skybox.glsl");
            fragmentSrc = AssetsManager::GetFragmentShaderSource("Shaders/Nova_Skybox.glsl");
            skyboxShader = Shader::Create(vertexSrc, fragmentSrc);
            skyboxVBO->Bind();
            skyboxVBO->SetPoint(0, 3, ShaderDataType::Float, false, 3 * sizeof(float), 0);
            skyboxVAO->Unbind();

            skyBoxTexture = CubeMap::Create(faces);
            //---------≤‚ ‘ÃÏø’∫–--------
        }
        void RenderTestObject()
        {   
            frameBuffer->Bind();

            for (Mesh mesh : testModel->meshes)
            {
                shader->Bind();
                shader->SetFloat3("lightCol", light.color);
                shader->SetFloat3("lightDir", light.direction);
                shader->SetFloat3("viewPos", mainCamera.transform.position);
                Renderer::Submit(shader, mesh, transform, mainCamera);
            }


            //---------≤‚ ‘ÃÏø’∫–--------
            glDepthFunc(GL_LEQUAL);

            skyboxVAO->Bind();
            skyboxShader->Bind();

            skyBoxTexture->Bind(0);
            skyboxShader->SetInt("skybox", 0);

            skyboxShader->SetMat4("view", glm::mat4(glm::mat3(mainCamera.transform.GetRotationMatrix())));
            skyboxShader->SetMat4("projection", mainCamera.GetProjectionMatrix());
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glDepthFunc(GL_LESS);

            ////---------≤‚ ‘ÃÏø’∫–--------  



                  
            frameBuffer->UnBind();
        }
        void TestImguiWindow()
        {
            ImGui::Begin("Rabbit");
            ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.01f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(transform.eulerAngle), 0.1f);
            ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.01f);
            ImGui::End();

            ImGui::Begin("Camera");
            ImGui::DragFloat3("Position", glm::value_ptr(mainCamera.transform.position), 0.01f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(mainCamera.transform.eulerAngle), 0.1f);
            ImGui::End();

            ImGui::Begin("Scene");
            ImVec2 size = ImGui::GetWindowSize();
            frameBuffer->SetTextureSize(size.x, size.y);
            ImGui::Image((void*)(intptr_t)frameBuffer->GetTextureID(), size, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::End();

        }
        //------------------------------------------

        //---------≤‚ ‘Scene----------
        Scene scene;

        void SceneInit()
        {
            auto gameObject = scene.CreateGameObject();
            gameObject->AddComponent<TestComponent>();
        }
        void SceneUpdate()
        {
            scene.Update();
        }
        //---------------------------
    };

    class NovaEditor : public Nova::Application
    {
    public:
        NovaEditor()
        {
            PushLayer(new EditorLayer());
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






