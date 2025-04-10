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
            static bool showDockSpace = true;
            ShowDockSpace(&showDockSpace);

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
            "G:/Nova/Assets/Textures/CubeMap/skybox/right.jpg",
            "G:/Nova/Assets/Textures/CubeMap/skybox/left.jpg",
            "G:/Nova/Assets/Textures/CubeMap/skybox/top.jpg",
            "G:/Nova/Assets/Textures/CubeMap/skybox/bottom.jpg",
            "G:/Nova/Assets/Textures/CubeMap/skybox/front.jpg",
            "G:/Nova/Assets/Textures/CubeMap/skybox/back.jpg"
        };
        //---------≤‚ ‘ÃÏø’∫–--------

        void RenderTestInit()
        {
            transform = std::make_shared<Transform>();
            light = std::make_shared<DirectionalLight>();

            light->color = glm::vec3(1.0f, 1.0f, 1.0f);
            light->direction = glm::vec3(0.0f, -1.0f, 0.0f);

            testModel = std::make_shared<Model>("G:/Nova/Assets/Models/Stanford/bunny_10k.obj");

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



        //-----------------ImGui---------------------------------------------------------------------
        static bool showScene;
        static bool showInspector;
        static bool showHierarchy;

        void SceneWindow()
        {
            if (showScene)
            {
                ImGui::Begin("Scene", &showScene);
                ImVec2 size = ImGui::GetWindowSize();
                frameBuffer->SetTextureSize(size.x, size.y);
                ImGui::Image((void*)(intptr_t)frameBuffer->GetTextureID(), size, ImVec2(0, 1), ImVec2(1, 0));
                ImGui::End();
            } 
        }

        std::shared_ptr<GameObject> selectedGameObject;
        void InspectorWinodw()
        {
            if (showInspector)
            {
                ImGui::Begin("Inspector", &showInspector);
                if (selectedGameObject)
                    selectedGameObject->OnImGui();
                ImGui::End();
            }
        }
        void HierarchyWindow()
        {
            if (showHierarchy)
            {
                ImGui::Begin("Hierarchy", &showHierarchy);

                for (auto [key, gameObject] : scene->GetGameObjects())
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

        void WindowsMenu()
        {
            if (ImGui::BeginMenu("Windows"))
            {
                if (ImGui::MenuItem("SceneWindow", NULL, false))
                    showScene = !showScene;

                if (ImGui::MenuItem("InspectorWindow", NULL, false))
                    showInspector = !showInspector;

                if (ImGui::MenuItem("HierarchyWindow", NULL, false))
                    showHierarchy = !showHierarchy;

                ImGui::EndMenu();
            }   
        }

        void ObjectMenu()
        {
            if (ImGui::BeginMenu("Object"))
            {
                if (ImGui::MenuItem("Create GameObject", NULL, false))
                {
                    scene->CreateGameObject();
                }
                ImGui::EndMenu();
            }
        }

        void ComponentMenu()
        {
            if (ImGui::BeginMenu("Component"))
            {
                bool selectAble = selectedGameObject != nullptr;

                if (ImGui::MenuItem("Add MeshRenderer", NULL, false, selectAble))
                {
                    selectedGameObject->AddComponent<MeshRenderer>();
                }
                if (ImGui::MenuItem("Add Camera", NULL, false, selectAble))
                {
                    selectedGameObject->AddComponent<Camera>();
                    scene->mainCamera = selectedGameObject->GetComponent<Camera>();
                    selectedGameObject->name = "mainCamera";
                }
                ImGui::EndMenu();
            }
        }

        void ShowDockSpace(bool* p_open)
        {
            static bool opt_fullscreen_persistant = true;
            static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
            bool opt_fullscreen = opt_fullscreen_persistant;
            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen)
            {
                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->Pos);
                ImGui::SetNextWindowSize(viewport->Size);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }
            // When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
                window_flags |= ImGuiWindowFlags_NoBackground;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", p_open, window_flags);
            ImGui::PopStyleVar();
            if (opt_fullscreen)
                ImGui::PopStyleVar(2);
            ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);

            ImGui::BeginMenuBar();
            
            WindowsMenu();
            ObjectMenu();
            ComponentMenu();
            
            ImGui::EndMenuBar();

            ImGui::End();
        }

        //---------------------------------------------------------------------------------------------

        //---------≤‚ ‘Scene----------
        std::shared_ptr<Scene> scene;

        void SceneInit()
        {
            scene = std::make_shared<Scene>();
            scene->light = light;
            /*auto cameraGO = scene->CreateGameObject();
            mainCamera = cameraGO->AddComponent<Camera>();
            cameraGO->name = "mainCamera";
            scene->mainCamera = mainCamera;
            for (int i = 0; i < 5; i++)
            {
                auto gameObject = scene->CreateGameObject();
                auto renderer = gameObject->AddComponent<MeshRenderer>();
                renderer->SetShader(shader);
            }*/
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





    bool EditorLayer::showScene = false;
    bool EditorLayer::showInspector = false;
    bool EditorLayer::showHierarchy = false;

}






