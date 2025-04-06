/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */


#include "pch.h"
#include "WindowsWindow.h"
#include "Engine\Event\ApplicationEvent.h"
#include "Engine\Event\KeyEvent.h"
#include "Engine\Event\MouseEvent.h"
#include "Platform\OpenGL\OpenGLContext.h"


namespace Engine
{
    static bool GLFWInitialized = false;

    static void GLFWErrorCallback(i32 errorCode, const char * description)
    {
        ENGINE_CORE_ERROR("GLFW Error ({0}): {1}", errorCode, description);
    }

    Window * Window::Create(const WindowProps & windowProps)
    {
        return new WindowsWindow(windowProps);
    }

    WindowsWindow::WindowsWindow(const WindowProps & windowProps)
    {
        Init(windowProps);
    }

    WindowsWindow::~WindowsWindow()
    {
        ShutDown();
    }

    void WindowsWindow::Init(const WindowProps & windowProps)
    {
        data.title = windowProps.title;
        data.width = windowProps.width;
        data.height = windowProps.height;

        ENGINE_CORE_INFO("Creating Window {0} ({1}, {2})", data.title, data.width, data.height);

        if (!GLFWInitialized)
        {
            //TODO: glfwTerminate on system shutdown
            ENGINE_CORE_ASSERT(glfwInit(), "Counld not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            GLFWInitialized = true;
        }

        
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
        
        window = glfwCreateWindow(
            data.width,
            data.height,
            data.title.c_str(),
            nullptr,
            nullptr);
        ENGINE_CORE_ASSERT(window != nullptr, "Could not create window  ");

        context = new OpenGLContext(window);        
        context->Init();
        GLFWmonitor * primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode * videoMode = glfwGetVideoMode(primaryMonitor);
        const i32 windowLeft = videoMode->width / 2 - data.width / 2;
        const i32 windowTop = videoMode->height / 2 - data.height / 2;
        glfwSetWindowPos(window, windowLeft, windowTop);
        glfwSetWindowUserPointer(window, &data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* _window, int width, int height)
        {
            WindowData & _data = *(WindowData *)glfwGetWindowUserPointer(_window);
            _data.width = width;
            _data.height = height;

            WindowResizeEvent event(width, height);
            _data.EventCallback(event);
        });

        glfwSetCharCallback(window, [](GLFWwindow * _window, u32 codePoint)
        {
            WindowData & _data = *(WindowData *)glfwGetWindowUserPointer(_window);
            KeyTypedEvent event(codePoint);
            _data.EventCallback(event);
        });
        
        glfwSetWindowCloseCallback(window, [](GLFWwindow * _window)
        {
            WindowData & _data = *(WindowData *)glfwGetWindowUserPointer(_window);
            WindowCloseEvent event;
            _data.EventCallback(event);
            
        });

        glfwSetKeyCallback(window, [](GLFWwindow * _window, i32 key, i32 scancode, i32 action, i32 mods)
        {
            WindowData & _data = *(WindowData *)glfwGetWindowUserPointer(_window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, mods, 0);
                    _data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key, mods);
                    _data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    
                    KeyPressedEvent event(key, mods, 1);
                    _data.EventCallback(event);
                    break;
                }
                default: {}
            }

        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow * _window, i32 button, i32 action, i32 mods)
        {
            WindowData & _data = *(WindowData *)glfwGetWindowUserPointer(_window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MousePressedEvent event(button);
                    _data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseReleasedEvent event(button);
                    _data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    
                }
                default: {}
            }
            
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow * _window, r64 xpos, r64 ypos)
        {
            WindowData & _data = *(WindowData *)glfwGetWindowUserPointer(_window);

            MouseMovedEvent event((r32)xpos, (r32)ypos);
            _data.EventCallback(event);
        });

        glfwSetScrollCallback(window, [](GLFWwindow * _window, r64 xoffset, r64 yoffset)
        {
            WindowData & _data = *(WindowData *)glfwGetWindowUserPointer(_window);

            MouseScrolledEvent event((r32)xoffset, (r32)yoffset);
            _data.EventCallback(event);
        });

#ifdef GLFW_INCLUDE_VULKAN
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        ENGINE_CORE_TRACE("{0}  extensions supported", extensionCount);
#endif
    }

    void WindowsWindow::ShutDown()
    {
        glfwDestroyWindow(window);

    }

    void WindowsWindow::OnUpdate() 
    {
        glfwPollEvents();
        context->SwapBuffers();
    }
    
    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return data.VSync;
    }
}
