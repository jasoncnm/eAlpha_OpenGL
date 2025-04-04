#if !defined(WINDOWSWINDOW_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Window.h"
#include "Engine/Renderer/GraphicsContext.h"

#ifdef ENGINE_API_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif

#include <GLFW/glfw3.h>


namespace Engine
{

    class  WindowsWindow : public Window
    {
    public: 

        WindowsWindow(const WindowProps & windowProps);
        virtual ~WindowsWindow();
        inline u32 GetWidth() const override { return data.width; }
        inline u32 GetHeight() const override { return data.height; }

        void OnUpdate() override;
        
        // Window Attributes
        inline void SetEventCallback(const EventCallbackFn & callback) override { data.EventCallback = callback; } 

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void * GetNativeWindow() const override { return window; };

    private:

        virtual void Init(const WindowProps & windowProps);
        virtual void ShutDown();
        
        GLFWwindow * window = nullptr;
        GraphicsContext * context;

        struct WindowData
        {
            std::string title = "Windows Window";
            u32 width = 1920, height = 1080;
            bool VSync = false;
            EventCallbackFn EventCallback;
        };
        
        WindowData data;
            
    };

}


#define WINDOWSWINDOW_H
#endif
