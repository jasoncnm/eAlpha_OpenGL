/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace Engine
{
    VertexBuffer * VertexBuffer::Create(float * vertices, u32 size)
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
                return new OpenGLVertexBuffer(vertices, size);
            }
        }
        ENGINE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }

    
    IndexBuffer * IndexBuffer::Create(u32 * indices, u32 count)
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
                return new OpenGLIndexBuffer(indices, count);
            }
        }
        ENGINE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;

    }
   
}
