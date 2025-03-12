#include <Nova.h>


#include "Core/NovaAssetsManager.h"

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

#include <json/json.h>

#include <filesystem>
#include <fstream>
#include <iostream>
//---------------------


namespace Nova
{
    class EditorLayer : public Nova::Layer
    {
    public:
        EditorLayer()
            : Layer("Example")
        {

        }

        void OnAttach() override
        {
            //≤‚ ‘≥ı ºªØ-------
            RenderTestInit();
            SceneInit();
            JsoncppTest();
            //----------------
        }

        void OnUpdate(Nova::Timestep ts) override
        {
            Nova::Renderer::BeginScene(scene);
            Nova::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Nova::RenderCommand::Clear();

            //Scene≤‚ ‘«¯º‰----
            frameBuffer->Bind();
            SceneUpdate();
            RendererSkyBox();
            frameBuffer->UnBind();
            //----------------

            Nova::Renderer::EndScene();
        }

        virtual void OnImGuiRender() override
        {
            ShowViewPortWindow();
            HierarchyWindow();
            InspectorWinodw();
            SceneWindow();
            SaveSceneWindow();
        }

        void OnEvent(Nova::Event& event) override
        {

        }

    private:

        void ShowViewPortWindow()
        {
            
        }


        //----------------≤‚ ‘¥˙¬Î«¯------------------

        //---------≤‚ ‘jsoncpp-----------------


        void JsoncppTest()
        {
            std::string path = "E:/Nova/Assets/JSON";
            std::filesystem::create_directories(path);
            path += "/test.json";

            auto file = std::ofstream(path);
            if (file)
            {
                Json::Value test;
                test["Test"] = 123;
                file << test;
            }
            file.close();

            Json::Value root;
            std::ifstream file2(path);
            Json::CharReaderBuilder builder;
            if (!Json::parseFromStream(builder, file2, &root, nullptr))
            {
                std::cout << "JsoncppTest: parseFromStream failed" << std::endl;
            }
            std::cout << root["Test"].asInt() << std::endl;
            
        }

        //-------------------------------------
        std::shared_ptr<Camera> mainCamera;
        std::shared_ptr <DirectionalLight> light;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Transform> transform;

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
            transform = std::make_shared<Transform>();
            light = std::make_shared<DirectionalLight>();

            light->color = glm::vec3(1.0f, 1.0f, 1.0f);
            light->direction = glm::vec3(0.0f, -1.0f, 0.0f);

            testModel = std::make_shared<Model>("E:/Nova/Assets/Models/Stanford/bunny_10k.obj");

            std::string vertexSrc = NovaAssetsManager::GetVertexShaderSource("Shaders/Nova_Standard.glsl");
            std::string fragmentSrc = NovaAssetsManager::GetFragmentShaderSource("Shaders/Nova_Standard.glsl");
            // ¥¥Ω®◊≈…´∆˜
            shader = Shader::Create(vertexSrc, fragmentSrc);

            frameBuffer = FrameBuffer::Create();
            frameBuffer->SetTextureSize(1920, 1080);

            //---------≤‚ ‘ÃÏø’∫–--------
            skyboxVAO = VertexArray::Create();
            skyboxVAO->Bind();
            skyboxVBO = VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
            vertexSrc = NovaAssetsManager::GetVertexShaderSource("Shaders/Nova_Skybox.glsl");
            fragmentSrc = NovaAssetsManager::GetFragmentShaderSource("Shaders/Nova_Skybox.glsl");
            skyboxShader = Shader::Create(vertexSrc, fragmentSrc);
            skyboxVBO->Bind();
            skyboxVBO->SetPoint(0, 3, ShaderDataType::Float, false, 3 * sizeof(float), 0);
            skyboxVAO->Unbind();

            skyBoxTexture = CubeMap::Create(faces);
            //---------≤‚ ‘ÃÏø’∫–--------
        }
        void RendererSkyBox()
        {
            if (scene->mainCamera == nullptr)
                return;

            glDepthFunc(GL_LEQUAL);
            skyboxVAO->Bind();
            skyboxShader->Bind();

            skyBoxTexture->Bind(0);
            skyboxShader->SetInt("skybox", 0);

            skyboxShader->SetMat4("view", glm::mat4(glm::mat3(scene->mainCamera->gameObject->transform->GetRotationMatrix())));
            skyboxShader->SetMat4("projection", scene->mainCamera->GetProjectionMatrix());
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthFunc(GL_LESS);
        }
        void SceneWindow()
        {
            ImGui::Begin("Scene");
            ImVec2 size = ImGui::GetWindowSize();
            frameBuffer->SetTextureSize(size.x, size.y);
            ImGui::Image((void*)(intptr_t)frameBuffer->GetTextureID(), size, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::End();
        }

        std::shared_ptr<GameObject> selectedGameObject;
        void InspectorWinodw()
        {
            ImGui::Begin("Inspector");
            if (selectedGameObject)
                selectedGameObject->OnImGui();
            ImGui::End();
        }
        void HierarchyWindow()
        {
            ImGui::Begin("Hierarchy");

            for (auto [key,gameObject] : scene->GetGameObjects())
            {
                ImGui::PushID(gameObject->id);
                bool isSelected = (selectedGameObject == gameObject);
                if (ImGui::Selectable(gameObject->name.c_str(), isSelected))
                {
                    selectedGameObject = gameObject;
                }
                ImGui::PopID();
            }

            ImGui::End();

        }
        void SaveSceneWindow()
        {
            ImGui::Begin("SceneEditor");
            if (ImGui::Button("Save"))
            {
                scene->SaveScene("E:/Nova/Assets/Scenes", "test");
            }
            if (ImGui::Button("Load"))
            {
                Json::Value root;
                std::ifstream file("E:/Nova/Assets/Scenes/test.json");
                Json::CharReaderBuilder builder;
                if (!Json::parseFromStream(builder, file, &root, nullptr))
                {
                    NOVA_ERROR("Failed to parse JSON");
                    return;
                }
                scene->FromJson(root);
                scene->FindCameraFromGameObjects();
                file.close();
            }
            ImGui::End();
        }
        //------------------------------------------

        //---------≤‚ ‘Scene----------
        std::shared_ptr<Scene> scene;

        void SceneInit()
        {
            scene = std::make_shared<Scene>();
            scene->light = light;
            //auto cameraGO = scene->CreateGameObject();
            //mainCamera = cameraGO->AddComponent<Camera>();
            //cameraGO->name = "mainCamera";
            //scene->mainCamera = mainCamera;
            //for (int i = 0; i < 5; i++)
            //{
            //    auto gameObject = scene->CreateGameObject();
            //    auto renderer = gameObject->AddComponent<MeshRenderer>();
            //    renderer->SetShader(shader);
            //}
        }
        void SceneUpdate()
        {
            scene->Update();
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






