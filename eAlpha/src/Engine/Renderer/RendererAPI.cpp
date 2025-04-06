/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "RendererAPI.h"

namespace Engine
{
#ifdef ENGINE_API_OPENGL
    RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;
#elif ENGINE_API_VULKAN
    RendererAPI::API RendererAPI::api = RendererAPI::API::Vulkan;
#endif
}
