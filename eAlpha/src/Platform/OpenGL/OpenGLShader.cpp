/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */
#include "pch.h"
#include "OpenGLShader.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{

    
    OpenGLShader::OpenGLShader(std::string vertexSource, std::string fragmentSource)
    {

        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar *source = (const GLchar *)vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
    
            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            ENGINE_CORE_ERROR("{0}", infoLog.data());
            ENGINE_CORE_ASSERT(false, "fail to create vertex shader!");
            // In this simple program, we'll just leave
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar *)fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
    
            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            ENGINE_CORE_ERROR("{0}", infoLog.data());
            ENGINE_CORE_ASSERT(false, "fail to create fragment shader!");    
            // In this simple program, we'll just leave
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        rendererId = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(rendererId, vertexShader);
        glAttachShader(rendererId, fragmentShader);

        // Link our program
        glLinkProgram(rendererId);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(rendererId, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(rendererId, maxLength, &maxLength, &infoLog[0]);
    
            // We don't need the program anymore.
            glDeleteProgram(rendererId);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            // Use the infoLog as you see fit.
            ENGINE_CORE_ERROR("{0}", infoLog.data());
            ENGINE_CORE_ASSERT(false, "shaders link failure!");    
    
            // In this simple program, we'll just leave
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(rendererId, vertexShader);
        glDetachShader(rendererId, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(rendererId);

    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(rendererId);

    }

    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);

    }

    u32 OpenGLShader::GetAttribLocation(const char * attribName)
    {
        u32 result = glGetAttribLocation(rendererId, (const GLchar *)attribName);

        if (result == -1) {

            ENGINE_CORE_ERROR("Error obtaining attribute location: {0}", attribName);
            ENGINE_CORE_ASSERT(false, "Attribute Location ERROR!");
        }
        return result;
    }

    void OpenGLShader::UploadUniformMat4(const std::string & name, const glm::mat4 & matrix)
    {
        i32 location = glGetUniformLocation(rendererId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformVec3(const std::string & name, const glm::vec3 & value)
    {
        i32 location = glGetUniformLocation(rendererId, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }
    
}
