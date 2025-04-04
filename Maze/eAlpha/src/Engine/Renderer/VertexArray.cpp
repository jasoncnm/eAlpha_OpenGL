/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
        
    VertexArray * VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
            {
                ENGINE_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
            {
                return new OpenGLVertexArray();
            }
        }
        ENGINE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;

    }

}
