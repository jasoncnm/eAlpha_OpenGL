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
    }
    
    
    void Renderer::BeginScene(ProjectionCamera & camera, glm::mat4 & model)
    {
        sceneData->viewProj = camera.GetVPMatrix();
        sceneData->model = model;
    }

    void Renderer::DrawTypeTriangles()
    {
        RenderCommand::DrawTypeTriangles();
    }

    void Renderer::DrawTypeLines()
    {
        RenderCommand::DrawTypeLines();
    }
    
    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> & vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("VP", sceneData->viewProj);
        shader->UploadUniformMat4("M", sceneData->model);
        
        vertexArray->Bind();
        RenderCommand::DrawIndex(vertexArray);
    }

    void Renderer::Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> & vertexArray, const glm::vec3 uniformColor)
    {
        shader->Bind();
        shader->UploadUniformMat4("VP", sceneData->viewProj);
        shader->UploadUniformMat4("M", sceneData->model);
        
        vertexArray->Bind();
        shader->UploadUniformVec3("color", uniformColor);
        RenderCommand::DrawIndex(vertexArray);
    }

}
