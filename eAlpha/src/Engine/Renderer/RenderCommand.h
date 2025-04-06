#if !defined(RENDERCOMMAND_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "RendererAPI.h"

namespace Engine
{
    class RenderCommand
    {
    public:

        static inline void SetClearColor(const glm::vec4 & color) { rendererAPI->SetClearColor(color); }

        static inline void Clear() { rendererAPI->Clear(); }

        static inline void EnableDepthTest() { rendererAPI->EnableDepthTest(); }

        static inline void DrawTypeTriangles() { rendererAPI->DrawTypeTriangles(); }

        static inline void DrawTypeLines() { rendererAPI->DrawTypeLines(); }
 
        inline static void DrawIndex(const std::shared_ptr<VertexArray> & vertexArray)
        {
            rendererAPI->DrawIndex(vertexArray);
        }

    private:
        static RendererAPI * rendererAPI;
    };
}

#define RENDERCOMMAND_H
#endif
