/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "OpenGLRendererAPI.h"

namespace Engine
{

    void OpenGLRendererAPI::SetClearColor(const glm::vec4 & color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::EnableDepthTest()
    {
        glEnable( GL_DEPTH_TEST );
    }
    
    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndex(const std::shared_ptr<VertexArray> & vertexArray)
    {
        glDrawElements(mode, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

}
