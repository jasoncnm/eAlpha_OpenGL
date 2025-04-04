/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */
#include "pch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

    OrthographicCamera::OrthographicCamera(r32 left, r32 right, r32 bottom, r32 top)
            : proj(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view(1.0f) 
    {
        viewProj = proj * view;
    }
    
    void OrthographicCamera::SetPosition(const glm::vec3 & position)
    {
        this->position = position;
        RecalculateViewMatrix();
    }
    
    void OrthographicCamera::SetRotation(r32 rotation)
    {
        this->rotation = rotation;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {

        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);

        glm::mat4 mat = translate * rotate;
        
        view = glm::inverse(mat);
        viewProj = proj * view;
    }

    ProjectionCamera::ProjectionCamera(glm::mat4 & proj, glm::mat4 & view)
            : proj(proj), view(view)
    {
        viewProj = proj * view;
    }

    void ProjectionCamera::SetPosition(const glm::vec3 & position)
    {
        this->position = position;
        RecalculateViewMatrix();
    }
    
    void ProjectionCamera::SetRotation(r32 rotation)
    {
        this->rotation = rotation;
        RecalculateViewMatrix();
    }

    void ProjectionCamera::RecalculateViewMatrix()
    {

        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);

        glm::mat4 mat = translate * rotate;
        
        view = glm::inverse(mat) * view;
        viewProj = proj * view;

    }


}
