#if !defined(GRAPHICCONTEXT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

namespace Engine
{
    
    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}

#define GRAPHICCONTEXT_H
#endif
