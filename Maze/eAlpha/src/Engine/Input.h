#if !defined(INPUT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Core.h"

namespace Engine
{

    class Input
    {
    public:

        inline static bool IsKeyPressed(i32 keyCode) { return instance->IsKeyPressedImpl(keyCode); }
        inline static bool IsMousePressed(i32 button) { return instance->IsMousePressedImpl(button); }
        inline static r32 GetMouseX() { return instance->GetMouseXImpl(); }        
        inline static r32 GetMouseY() { return instance->GetMouseYImpl(); }
        inline static std::pair<r32, r32> GetMousePos() { return instance->GetMousePosImpl(); }
        

    protected:
        virtual bool IsKeyPressedImpl(i32 keyCode) = 0;
        virtual bool IsMousePressedImpl(i32 button) = 0;
        virtual r32 GetMouseXImpl() = 0;
        virtual r32 GetMouseYImpl() = 0;
        virtual std::pair<r32, r32> GetMousePosImpl() = 0;
        
    private:
        static Input * instance;
    };

}
#define INPUT_H
#endif
