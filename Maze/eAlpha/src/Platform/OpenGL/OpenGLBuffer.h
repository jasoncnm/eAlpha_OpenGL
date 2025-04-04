#if !defined(OPENGLBUFFER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Renderer/Buffer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{
    
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:

        OpenGLVertexBuffer(float * vertices, u32 size);
        
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;

        void UnBind() const override;

        virtual const BufferLayout & GetLayout() const override { return layout; }
        virtual void SetLayout(const BufferLayout & layout) override { this->layout = layout; };
        
    private:
        u32 rendererId;
        BufferLayout layout;       
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:

        OpenGLIndexBuffer(u32 * indices, u32 count);
        
        virtual ~OpenGLIndexBuffer();

        u32 GetCount() const override { return count; }
        
        void Bind() const override;

        void UnBind() const override;

    private:
        u32 rendererId;
        u32 count;
    };
}

#define OPENGLBUFFER_H
#endif
