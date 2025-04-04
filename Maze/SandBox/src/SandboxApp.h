#if !defined(SANBOXAPP_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <Engine.h>
#include "Maze.h"


class MazeLayer : public Engine::Layer
{
public:
    MazeLayer();

    virtual void OnUpdate(Engine::TimeStep timeStep) override;
    virtual void OnEvent(Engine::Event& event) override;
    virtual void OnImGuiRender() override;

    bool OnMouseMoveEvent(Engine::MouseMovedEvent& event);
    bool OnMouseInputEvent(Engine::MouseButtonEvent& event);
    bool OnMouseScrollEvent(Engine::MouseScrolledEvent& event);
    bool OnWindowResizeEvent(Engine::WindowResizeEvent& event);
    bool OnKeyPressedEvent(Engine::KeyPressedEvent& event);
    bool OnKeyReleaseEvent(Engine::KeyReleasedEvent& event);

private:
    void initGrid();
    void initCubes();
    void initAvatar();
    void initFloor();
    void resetGridStates();
    void findStartPoint();
    bool noWall(int x, int y);

    // Fields related to the shader and uniforms.
    std::shared_ptr<Engine::Shader> shader;

    // Fields related to grid geometry.
    std::shared_ptr<Engine::VertexArray> gridVA; // Vertex Array Object
    std::shared_ptr<Engine::VertexArray> cubesVA;
    std::shared_ptr<Engine::VertexArray> avatarVao;
    std::shared_ptr<Engine::VertexArray> floorVao;

    // Matrices controlling the camera and projection.
    glm::mat4 proj;
    glm::mat4 view;

    std::unique_ptr<Maze> m;

    Engine::ProjectionCamera camera;

    float deltaX = 0.0f;
    float rotation = 0.0f;
    float persistence = 0.0f;
    float scaleSize = 1.0f;
    float widgetColor[3];
    float colorF[3];
    float colorW[3];
    float colorA[3];
    float xPrev;
    int last_col;
    int current_col;
    int cubeCount;
    int sectorCount = 20;
    int stackCount = 20;
    float cubeHeight;
    int  avatarPos[3];
    bool mouseButtonActive;

};


class SandBox : public Engine::Application
{
public:
    SandBox()
    {
        PushLayer(new MazeLayer());
    }
    ~SandBox() {}

};


#define SANBOXAPP_H
#endif
