#if !defined(RENDERER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Engine
{

    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera & camera);
        static void BeginScene(ProjectionCamera & camera, glm::mat4 & model);
        static void EndScene();

        static void DrawTypeTriangles();
        static void DrawTypeLines();

        static void Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> & vertexArray);
        static void Submit(std::shared_ptr<Shader> shader,
                           const std::shared_ptr<VertexArray> & vertexArray,
                           const glm::vec3 uniformColor);
        
        inline static RendererAPI::API  GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 viewProj;
            glm::mat4 model;
        };

        static SceneData * sceneData;
    };
}

#define RENDERER_H
#endif
