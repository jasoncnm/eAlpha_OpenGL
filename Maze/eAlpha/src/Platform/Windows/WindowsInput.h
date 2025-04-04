#if !defined(WINDOWSINPUT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Input.h"

namespace Engine
{

    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(i32 keyCode) override;
        virtual bool IsMousePressedImpl(i32 button) override;
        virtual r32 GetMouseXImpl() override;
        virtual r32 GetMouseYImpl() override;
        virtual std::pair<r32, r32> GetMousePosImpl() override;

    };
}


#define WINDOWSINPUT_H
#endif
