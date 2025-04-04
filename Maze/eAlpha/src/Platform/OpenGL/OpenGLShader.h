#if !defined(OPENGLSHADER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/Shader.h"
#include <glm/glm.hpp>
namespace Engine
{

    class OpenGLShader : public Shader
    {
    public:

        OpenGLShader(std::string vertexSource, std::string fragmentSource);

        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;
        virtual void UploadUniformMat4(const std::string & name, const glm::mat4 & matrix) override;
        virtual void UploadUniformVec3(const std::string & name, const glm::vec3 & value) override;

        virtual u32 GetAttribLocation(const char * attribName);

    private:
        u32 rendererId;
        
    };
    
}


#define OPENGLSHADER_H
#endif
