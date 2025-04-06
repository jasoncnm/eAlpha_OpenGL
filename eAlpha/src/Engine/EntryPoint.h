#if !defined(ENTRYPOINT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application * Engine::CreateApplication();

int main(int argc, char ** argv)
{
    
    Engine::Log::Init();
    ENGINE_CORE_WARN("Initialized Log!");
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
}

#endif

#define ENTRYPOINT_H
#endif
