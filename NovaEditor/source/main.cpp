#include <Nova.h>


#include "Core/AssetsManager.h"

#include "Nova/Platform/Opengl/OpenGLShader.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace NovaEditor;

//临时学习加入的库-------
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
            //测试初始化-------
            RenderTestInit();
            //----------------
        }

        void OnUpdate(Nova::Timestep ts) override
        {
            Nova::Renderer::BeginScene();
            Nova::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Nova::RenderCommand::Clear();

            //测试渲染区间------
            RenderTestObject();
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


        //----------------测试代码区------------------
        Camera mainCamera;
        DirectionalLight light;
        std::shared_ptr<Shader> shader;
        Transform transform;

        std::shared_ptr<Model> testModel;
        std::shared_ptr<FrameBuffer> frameBuffer;


        void RenderTestInit()
        {     
            testModel = std::make_shared<Model>("E:/Nova/Assets/Models/Stanford/bunny_10k.obj");            
            light.color = glm::vec3(1.0f, 1.0f, 1.0f);
            light.direction = glm::vec3(0.0f, -1.0f, 0.0f);

            std::string vertexSrc = AssetsManager::GetVertexShaderSource("Shaders/Nova_Standard.glsl");
            std::string fragmentSrc = AssetsManager::GetFragmentShaderSource("Shaders/Nova_Standard.glsl");
            // 创建着色器
            shader = Shader::Create(vertexSrc, fragmentSrc);    

            frameBuffer = FrameBuffer::Create();
            frameBuffer->SetTextureSize(1920, 1080);
        }
        void RenderTestObject()
        {   

            frameBuffer->Bind();

            /*if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                NOVA_ERROR("Framebuffer is not complete!");
            }*/

            for (Mesh mesh : testModel->meshes)
            {
                shader->SetFloat3("lightCol", light.color);
                shader->SetFloat3("lightDir", light.direction);
                shader->SetFloat3("viewPos", mainCamera.transform.position);
                Renderer::Submit(shader, mesh, transform, mainCamera);
            }     
            
            frameBuffer->UnBind();
        }

        void TestImguiWindow()
        {
            ImGui::Begin("Cube");
            ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.01f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(transform.eulerAngle), 0.01f);
            ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.01f);
            ImGui::End();

            ImGui::Begin("Camera");
            ImGui::DragFloat3("Position", glm::value_ptr(mainCamera.transform.position), 0.01f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(mainCamera.transform.eulerAngle), 0.01f);
            ImGui::End();

            ImGui::Begin("Scene");
            ImVec2 size = ImGui::GetWindowSize();
            frameBuffer->SetTextureSize(size.x, size.y);
            ImGui::Image((void*)(intptr_t)frameBuffer->GetTextureID(), size, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::End();

        }


        //------------------------------------------
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






