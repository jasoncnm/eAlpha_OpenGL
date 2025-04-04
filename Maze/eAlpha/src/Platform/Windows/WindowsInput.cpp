/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "WindowsInput.h"
#include "Engine/Application.h"
#include <GLFW/glfw3.h>

namespace Engine
{

    Input * Input::instance = new WindowsInput();
    
    bool WindowsInput::IsKeyPressedImpl(i32 keyCode)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());

        auto state = glfwGetKey(window, keyCode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMousePressedImpl(i32 button)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    r32 WindowsInput::GetMouseXImpl()
    {

        auto[x,y] = GetMousePosImpl();

        return x;
    }
    
    r32 WindowsInput::GetMouseYImpl()
    {

        auto[x,y] = GetMousePosImpl();
        
        return y;
    }

    std::pair<r32, r32> WindowsInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        r64 xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);

        std::pair<r32, r32> result{ (r32)xpos, (r32)ypos };
        
        return result;
    }

    
}
