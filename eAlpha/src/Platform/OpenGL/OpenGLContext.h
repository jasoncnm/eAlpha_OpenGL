#if !defined(OPENGLCONTEXT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace Engine
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow * windowHandle);
        
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:

        GLFWwindow * windowHandle;
        
    };
}

#define OPENGLCONTEXT_H
#endif
