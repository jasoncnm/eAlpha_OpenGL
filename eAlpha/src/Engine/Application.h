#if !defined(APPLICATION_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Window.h"
#include "Engine/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"

namespace Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event & event);
        void PushLayer(Layer * layer);
        void PushOverlay(Layer * overlay);
        
        void ExtractShaderSourceCode(std::string & shaderSource, const std::string & filePath);

        void Quit() { Running = false; } 
        
        inline static Application& Get() { return *instance; }
        inline Window & GetWindow() { return *window; }
        
    private:
    
        bool Running = true;
        bool OnWindowClose(WindowCloseEvent& event);

        std::unique_ptr<Window> window;

        ImGuiLayer * imGuiLayer;

        LayerStack layerStack;

        r32 lastFrameTime;
        
        static Application * instance;
    
    };
    Application * CreateApplication();
}

#define APPLICATION_H
#endif
