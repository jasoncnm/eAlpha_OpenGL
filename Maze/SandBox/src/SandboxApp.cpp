/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "SandboxApp.h"
#include "Assets/ShaderFiles.h"
#include <cstdlib>
#include <ctime>
#include <glm/gtc/matrix_transform.hpp>

const u32 DIM = 16;
const float PI = 3.14159265f;
const r32 M_SQRT1_2 = 0.707106781187f;

MazeLayer::MazeLayer()
    : Layer("Maze"), current_col(0), last_col(-1), mouseButtonActive(false),
    view(glm::lookAt(glm::vec3(0.0f, 2. * float(DIM) * 2.0 * M_SQRT1_2, float(DIM) * 2.0 * M_SQRT1_2),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f))),

    proj(glm::perspective(glm::radians(30.0f),
        (float)Engine::Application::Get().GetWindow().GetWidth() /
        (float)Engine::Application::Get().GetWindow().GetHeight(),
        1.0f,
        1000.0f)),
    camera(proj, view)
{
    colorF[0] = 0.5f;
    colorF[1] = 0.5f;
    colorF[2] = 0.5f;
    colorW[0] = 0.3f;
    colorW[1] = 0.3f;
    colorW[2] = 0.7f;
    colorA[0] = 0.7f;
    colorA[1] = 0.3f;
    colorA[2] = 0.3f;

    widgetColor[0] = 0.5f;
    widgetColor[1] = 0.5f;
    widgetColor[2] = 0.5f;


    avatarPos[0] = 0;
    avatarPos[1] = 0;
    avatarPos[2] = 0;

    // Initialize random number generator
    u32 seed = (u32)std::time({});
    std::srand(seed);
    // Print random number seed in case we want to rerun with
    // same random numbers
    ENGINE_INFO("Random number seed = {0}", seed);

    m = std::make_unique<Maze>(DIM);

    // Build the shader
    shader.reset(Engine::Shader::Create(ShaderFiles::mazeVS, ShaderFiles::mazeFS));

    cubeHeight = 1.0f;
    initFloor();
    initGrid();
    initCubes();
    initAvatar();

}

void MazeLayer::initGrid() {}
void MazeLayer::initCubes() {}
void MazeLayer::initAvatar() {}
void MazeLayer::initFloor() {}
void MazeLayer::resetGridStates() {}
void MazeLayer::findStartPoint() {}

bool MazeLayer::noWall(int x, int y)
{
    return false;
}


void MazeLayer::OnUpdate(Engine::TimeStep timeStep)
{
}

void MazeLayer::OnEvent(Engine::Event& event)
{
}

void MazeLayer::OnImGuiRender()
{

}


bool MazeLayer::OnMouseMoveEvent(Engine::MouseMovedEvent& event)
{
    return false;
}

bool MazeLayer::OnMouseInputEvent(Engine::MouseButtonEvent& event)
{
    return false;
}

bool MazeLayer::OnMouseScrollEvent(Engine::MouseScrolledEvent& event)
{
    return false;
}

bool MazeLayer::OnWindowResizeEvent(Engine::WindowResizeEvent& event)
{
    return false;
}

bool MazeLayer::OnKeyPressedEvent(Engine::KeyPressedEvent& event)
{
    return false;
}

bool MazeLayer::OnKeyReleaseEvent(Engine::KeyReleasedEvent& event)
{
    return false;
}



Engine::Application * Engine::CreateApplication()
{
    return new SandBox();
}
