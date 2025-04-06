/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "pch.h"
#include "OpenGLVertexArray.h"

namespace Engine
{

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
        }
        
        ENGINE_CORE_ASSERT(false, "Unknown Shader Data Type!");
        return 0;
 
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &rendererId);
    }
    
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &rendererId);
    }
        
    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(rendererId);
    }
    
    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> & vertexBuffer)
    {
        const BufferLayout & layout = vertexBuffer->GetLayout();
        ENGINE_CORE_ASSERT(layout.GetBufferElements().size(), "Vertex Buffer has no layout!");        
        
        glBindVertexArray(rendererId);
        vertexBuffer->Bind();

        i32 index = 0;

        for (auto it = layout.begin(); it != layout.end(); it++, index++)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                it->GetElementCount(),
                ShaderDataTypeToOpenGLBaseType(it->type),
                it->normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                (const void *)it->offset
                                  );            
        }

        vertexBuffers.push_back(vertexBuffer);
    }
    
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> & indexBuffer)
    {
        glBindVertexArray(rendererId);
        indexBuffer->Bind();
        this->indexBuffer = indexBuffer;
    }

}
