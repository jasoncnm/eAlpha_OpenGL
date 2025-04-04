#if !defined(MOUSEEVENT_H)
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
    class  MouseMovedEvent : public Event
    {
    public:

         MouseMovedEvent(r32 x, r32 y)
                : mouseX(x), mouseY(y) {}

        inline r32 GetX() const { return mouseX; }
        inline r32 GetY() const { return mouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        
    private:
        r32 mouseX, mouseY;
    };

    class  MouseScrolledEvent : public Event
    {
    public:

         MouseScrolledEvent(r32 x, r32 y)
                : offsetX(x), offsetY(y) {}

        inline r32 GetOffsetX() const { return offsetX; }
        inline r32 GetOffsetY() const { return offsetY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << offsetX << ", " << offsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        
    private:
        r32 offsetX, offsetY;
    };


    class  MouseButtonEvent : public Event
    {
    public:
        inline i32 GetButton() const { return button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

    protected:
        MouseButtonEvent(i32 button)
            : button(button) {}
    private:
        i32 button;
    };

    
    class  MousePressedEvent : public MouseButtonEvent
    {
    public:
        MousePressedEvent(i32 button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << GetButton();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
        
    };

    
    class  MouseReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseReleasedEvent(i32 button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseReleasedEvent: " << GetButton();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);

    };
        

}

#define MOUSEEVENT_H
#endif
