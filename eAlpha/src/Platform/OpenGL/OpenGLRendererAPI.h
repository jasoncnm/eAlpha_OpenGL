#if !defined(OPENGLRENDERERAPI_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/RendererAPI.h"
#include <glad\glad.h>

namespace Engine
{
    class OpenGLRendererAPI : public RendererAPI
    {

    public:

        virtual void SetClearColor(const glm::vec4 & color) override;
        virtual void Clear() override;
        virtual void DrawIndex(const std::shared_ptr<VertexArray> & vertexArray) override;
        virtual void EnableDepthTest() override;

        virtual void DrawTypeTriangles()
        {
            mode = GL_TRIANGLES;
        }

        virtual void DrawTypeLines()
        {
            mode = GL_LINES;
        }

    private:
        GLenum mode;
    };
}

#define OPENGLRENDERERAPI_H
#endif
