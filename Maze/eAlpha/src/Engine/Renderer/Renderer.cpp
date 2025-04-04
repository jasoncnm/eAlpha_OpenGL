/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "Renderer.h"

namespace Engine
{

    Renderer::SceneData * Renderer::sceneData = new Renderer::SceneData;

    
    void Renderer::BeginScene(OrthographicCamera & camera)
    {
        sceneData->viewProj = camera.GetVPMatrix();
        sceneData->model = glm::mat4(1.0f);
        sceneData->color = glm::vec3(0.0f);
    }
    
    
    void Renderer::BeginScene(ProjectionCamera & camera, glm::mat4 & model, glm::vec3 & color)
    {
        sceneData->viewProj = camera.GetVPMatrix();
        sceneData->model = model;
        sceneData->color = color;
    }
    
    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> & vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("VP", sceneData->viewProj);
        shader->UploadUniformMat4("M", sceneData->model);
        shader->UploadUniformVec3("color", sceneData->color);
        
        vertexArray->Bind();
        RenderCommand::DrawIndex(vertexArray);
    }

}
