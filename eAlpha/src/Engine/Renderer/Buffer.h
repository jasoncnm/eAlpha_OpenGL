#if !defined(BUFFER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

namespace Engine
{

    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool,
    };

    static u32 ShaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;
        }

        ENGINE_CORE_ASSERT(false, "Unknown Shader Data Type!");
        return 0;
    }
    
    struct BufferElement
    {
        std::string name;
        ShaderDataType type;
        u64 offset;
        u32 size;
        bool normalized;

        BufferElement() {}
        
        BufferElement(ShaderDataType type, const std::string name, bool normalized = false)
                : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
        {
        }

        u32 GetElementCount() const
        {
            switch(type)
            {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
            }
            
            ENGINE_CORE_ASSERT(false, "Unknown Shader Data Type!");
            return 0;
        }
            
    };
    
    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement> & elements)
                : elements(elements)
        {
            CalculateOffsetAndStride();
        }
            
        inline u32 GetStride() const { return stride; }
        inline const std::vector<BufferElement> & GetBufferElements() const { return elements; }

        std::vector<BufferElement>::iterator begin() { return elements.begin(); }
        std::vector<BufferElement>::iterator end() { return elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
        
    private:
        std::vector<BufferElement> elements;
        u32 stride;

        void CalculateOffsetAndStride()
        {
            u64 offset = 0;
            stride = 0;
            for (BufferElement & element : elements)
            {
                element.offset = offset;
                offset += element.size;
                stride += element.size;
            }
        }
    };
    
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual const BufferLayout & GetLayout() const = 0; 
        virtual void SetLayout(const BufferLayout &layout) = 0;
        
        static VertexBuffer * Create(float * vertices, u32 size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual u32 GetCount() const = 0;
        
        static IndexBuffer * Create(u32 * indices, u32 count);        
    };

}

#define BUFFER_H
#endif
