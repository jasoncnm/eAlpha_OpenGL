#if !defined(CAMERA_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <glm/glm.hpp>

namespace Engine
{

    class Camera
    {
    public:
        
        virtual const glm::vec3 & GetPosition() const = 0;
        virtual const r32 GetRotation() const = 0;

        virtual const glm::mat4 & GetProjectionMatrix() const = 0;
        virtual const glm::mat4 & GetViewMatrix() const = 0;
        virtual const glm::mat4 & GetVPMatrix() const = 0;

    };
    
    class OrthographicCamera : Camera
    {
    public:

        OrthographicCamera(r32 left, r32 right, r32 bottom, r32 top);

        void SetPosition(const glm::vec3 & position);    
        void SetRotation(r32 rotation);
        
        virtual const glm::vec3 & GetPosition() const { return position; }
        virtual const r32 GetRotation() const { return rotation; }

        virtual const glm::mat4 & GetProjectionMatrix() const { return proj; }
        virtual const glm::mat4 & GetViewMatrix() const { return view; }
        virtual const glm::mat4 & GetVPMatrix() const { return viewProj; }
        
    private:

        void RecalculateViewMatrix();
        
        glm::mat4 proj;
        glm::mat4 view;
        glm::mat4 viewProj;

        glm::vec3 position = glm::vec3(0.0f);
        r32 rotation = 0.0f;
    };

    class ProjectionCamera : Camera
    {
    public:
        ProjectionCamera(glm::mat4 & proj, glm::mat4 & view);

        void SetViewMatrix(const glm::mat4 & view);
        void SetPosition(const glm::vec3 & position);    
        void SetRotation(r32 rotation);
        
        virtual const glm::vec3 & GetPosition() const { return glm::vec3(0); }
        virtual const r32 GetRotation() const { return 0; }

        virtual const glm::mat4 & GetProjectionMatrix() const { return proj; }
        virtual const glm::mat4 & GetViewMatrix() const { return view; }
        virtual const glm::mat4 & GetVPMatrix() const { return viewProj; }
        

    private:
        
        glm::mat4 proj;
        glm::mat4 view;
        glm::mat4 viewProj;

    };
}

#define CAMERA_H
#endif
