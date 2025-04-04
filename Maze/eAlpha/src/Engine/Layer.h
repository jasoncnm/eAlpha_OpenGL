#if !defined(LAYER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "Engine/Core.h"
#include "Engine/Event/Event.h"
#include "Engine/TimeStep.h"

namespace Engine
{

    class Layer
    {
    public:
        Layer(const std::string & name = "Layer");
        virtual ~Layer();

        virtual void OnAttatch() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(TimeStep timeStep) {}
        virtual void OnEvent(Event & event) {}
        virtual void OnImGuiRender() {}

        inline const std::string GetName() { return debugName; }

    private:
        std::string debugName;
    };

}

#define LAYER_H
#endif
