#if !defined(WINDOW_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"

#include "Engine/Event/Event.h"

namespace Engine
{
    struct WindowProps
    {
        std::string title;
        u32 width;
        u32 height;

        WindowProps(std::string title = "eAlpha Engine", u32 width = 1920, u32 height = 1080)
                : title(title), width(width), height(height) {}
    };

    // Interface Representing a desktop system based window
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        virtual ~Window() {}
        virtual void OnUpdate() = 0;
        virtual u32 GetWidth() const = 0;
        virtual u32 GetHeight() const = 0;

        // Window Attributes
        virtual void SetEventCallback(const EventCallbackFn & callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        virtual void * GetNativeWindow() const = 0;
        

        static Window * Create(const WindowProps & props = WindowProps());

    };
}

#define WINDOW_H
#endif
