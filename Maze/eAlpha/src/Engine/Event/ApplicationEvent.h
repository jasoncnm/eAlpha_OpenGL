#if !defined(APPLICATIONEVENT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Event.h"

namespace Engine
{
    class WindowCloseEvent : public Event
    {
public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
private:
    };

    class WindowResizeEvent : public Event
    {
public:
        WindowResizeEvent(u32 width, u32 height)
            : width(width), height(height) {}

        inline u32 GetWidth() { return width; }
        inline u32 GetHeight() { return height; }

        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << width << ", " << height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);


private:
        u32 width, height;
    };

    class AppTickEvent : public Event
    {
public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
    };

    class AppUpdateEvent : public Event
    {
public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
    };

    class AppRenderEvent : public Event
    {
public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
    };
    
}

#define APPLICATIONEVENT_H
#endif
