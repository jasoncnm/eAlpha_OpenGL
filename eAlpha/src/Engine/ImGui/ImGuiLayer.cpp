/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */
#include "pch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
 
#include "Engine\Application.h"

#include "Engine\Event\MouseEvent.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Engine
{

    ImGuiLayer::ImGuiLayer()
            : Layer("Example")
    {

    }
    
    ImGuiLayer::~ImGuiLayer()
    {

    }
    

    void ImGuiLayer::Begin()
    {

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application & app = Application::Get();
        io.DisplaySize = ImVec2((r32)app.GetWindow().GetWidth(), (r32)app.GetWindow().GetHeight());
        
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
 
    }

    void ImGuiLayer::OnImGuiRender()
    {
        // static bool show = false;
        // ImGui::ShowDemoWindow(&show);

    }
    
        
    
    void ImGuiLayer::OnAttatch()
    {
        
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        
        // Setup Platform/Renderer backends
        Application & app = Application::Get();

        GLFWwindow * window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());
        
        ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
        ImGui_ImplOpenGL3_Init("#version 410");

    }

    void ImGuiLayer::OnDetach()
    {        
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();        
    }

}
