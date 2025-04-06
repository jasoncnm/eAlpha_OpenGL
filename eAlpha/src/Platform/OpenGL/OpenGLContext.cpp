/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */
#include "pch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad\glad.h>

namespace Engine
{
    OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
            : windowHandle(windowHandle) {}
        
    void OpenGLContext::Init()
    {        
        glfwMakeContextCurrent(windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ENGINE_CORE_ASSERT(status, "Failed to initialize Glad!");

        char * vendor = (char *)glGetString(GL_VENDOR);
        char * renderer = (char *)glGetString(GL_RENDERER);
        char * version = (char *)glGetString(GL_VERSION);
        
        ENGINE_CORE_INFO("OpenGL info: ");
        ENGINE_CORE_INFO("  vendor: {0}", vendor);
        ENGINE_CORE_INFO("  renderer: {0}", renderer);        
        ENGINE_CORE_INFO("  version: {0}", version);
        
    }
    
    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(windowHandle);
    }

}

