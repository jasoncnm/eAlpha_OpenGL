#if !defined(TIMESTEP_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

namespace Engine
{
    class TimeStep
    {
    public:
        TimeStep(r32 t) : time(t) {}

        r32 GetSeconds() const { return time; }
        r32 GetMilliSeconds() const { return 1000.0f * time; }

        operator r32() const { return time; }
        
    private:
        r32 time;
    };
}

#define TIMESTEP_H
#endif
