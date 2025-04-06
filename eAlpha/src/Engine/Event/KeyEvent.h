#if !defined(KEYEVENT_H)
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

    class  KeyEvent : public Event
    {
    public:
        inline i32 GetKeyCode() const { return keyCode; }
        inline i32 GetMods() const { return keyMod; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

    protected:
        KeyEvent(i32 keyCode, i32 keyMod = 0)
                : keyCode(keyCode), keyMod(keyMod) {}

        i32 keyCode;
        i32 keyMod;
    };

    class  KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(i32 keycode, i32 keyMod, i32 repeatCount)
                : KeyEvent(keycode, keyMod), m_RepeatCount(repeatCount) {}

        inline i32 GetRepeatCount() { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << keyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed);
        
    private:
        i32 m_RepeatCount;

    };

    class  KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(i32 keycode, i32 keyMod)
                : KeyEvent(keycode, keyMod) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);

    };

    class  KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(i32 keycode)
                : KeyEvent(keycode) {}

        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped);
    };
}

#define KEYEVENT_H
#endif
