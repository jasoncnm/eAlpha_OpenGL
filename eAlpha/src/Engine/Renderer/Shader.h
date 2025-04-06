#if !defined(SHADER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <string>
#include <glm/glm.hpp>
namespace Engine
{
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual void UploadUniformMat4(const std::string & name, const glm::mat4 & matrix) = 0;
        virtual void UploadUniformVec3(const std::string & name, const glm::vec3 & value) = 0;

        virtual u32 GetAttribLocation(const char * attribName) = 0;

        static Shader * Create(std::string vertexSource, std::string fragmentSource);
        
    }; 
}

#define SHADER_H
#endif
