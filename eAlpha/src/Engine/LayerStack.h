#if !defined(LAYERSTACK_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Core.h"
#include "Layer.h"

#include <vector>

namespace Engine
{

    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer * layer);
        void PushOverlay(Layer * overlay);
        void PopLayer(Layer * layer);
        void PopOverlay(Layer * overlay);

        std::vector<Layer *>::iterator begin() { return layers.begin(); }
        std::vector<Layer *>::iterator end() { return layers.end(); }

    private:
        std::vector<Layer *> layers;
        u32 layerInsertIndex = 0;

    };

}

#define LAYERSTACK_H
#endif
