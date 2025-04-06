/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include "SandboxApp.h"
#include "Assets/ShaderFiles.h"
#include "imgui/imgui.h"
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
    m->digMaze();
    m->printMaze();
    findStartPoint();        
    // Build the shader
    shader.reset(Engine::Shader::Create(ShaderFiles::mazeVS, ShaderFiles::mazeFS));

    cubeHeight = 1.0f;
    initFloor();
    initGrid();
    initCubes();
    initAvatar();

}

void MazeLayer::initGrid()
{
    size_t sz = 3 * 2 * 2 * (DIM+3);

    u32  * indices = new u32[sz/3];
    r32 * verts = new r32[sz];

    size_t ct = 0;
    for( int idx = 0; idx < DIM + 3 ; ++idx ) {
        // NOTE: End points of horiziontal grid lines
        verts[ ct ] = -1;
        verts[ ct+1 ] = 0;
        verts[ ct+2 ] = idx-1;
        verts[ ct+3 ] = DIM+1;
        verts[ ct+4 ] = 0;
        verts[ ct+5 ] = idx-1;
        ct += 6;
        // NOTE: End points of vertical grid lines
        verts[ ct ] = idx-1;
        verts[ ct+1 ] = 0;
        verts[ ct+2 ] = -1;
        verts[ ct+3 ] = idx-1;
        verts[ ct+4 ] = 0;
        verts[ ct+5 ] = DIM+1;
        ct += 6;
    }

    for ( int i = 0; i < sz / 3; i++)
    {
        indices[i] = i;
    }
    
    std::shared_ptr<Engine::VertexBuffer> gridVB;
    std::shared_ptr<Engine::IndexBuffer>  gridIB;
    
    gridVA.reset(Engine::VertexArray::Create());

    gridVB.reset(Engine::VertexBuffer::Create(verts, sz * sizeof(r32)));
    Engine::BufferLayout layout = { { Engine::ShaderDataType::Float3, "position" } };
    gridVB->SetLayout(layout);

    gridVA->AddVertexBuffer(gridVB);

    gridIB.reset(Engine::IndexBuffer::Create(indices, sz/3));
    gridVA->SetIndexBuffer(gridIB);
}




void MazeLayer::initCubes()
{
    u32 cubeCount = 0;
    u32 mazeDim = m->getDim();

    std::vector<glm::vec3> cubesVertices;
    
    for (u32 x = 0; x < mazeDim; x++) {
        for (u32 y = 0; y < mazeDim; y++) {
            if (m->getValue(x, y) == 1) {
                cubeCount += 1;
                glm::vec3 ref = glm::vec3((float)x, 0.0f, (float)y);
                // NOTE: Botton face
                cubesVertices.push_back(ref);
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, 0.0f, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, 0.0f, 1.0f));
                // NOTE: Back face
                cubesVertices.push_back(ref);
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 0.0f));
                // NOTE: Left face
                cubesVertices.push_back(ref);
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, 0.0f, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, 0.0f, 1.0f));
                // NOTE: Right face
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 1.0f));
                // NOTE: Front face
                cubesVertices.push_back(ref + glm::vec3(0.0f, 0.0f, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, 0.0f, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 1.0f));
                // NOTE: Top face
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 1.0f));
                cubesVertices.push_back(ref + glm::vec3(1.0f, cubeHeight, 0.0f));
                cubesVertices.push_back(ref + glm::vec3(0.0f, cubeHeight, 1.0f));
            }
        }
    }

    u32 size = cubeCount * 6 * 6;
    
    u32* indices = new u32[size];
    r32* vertices = new r32[size * 3];
    u32 index = 0;
    u32 i = 0;
    for (glm::vec3 v : cubesVertices)
    {
        indices[i] = i;
        i++;
        vertices[index++] = v.x;
        vertices[index++] = v.y;
        vertices[index++] = v.z;
    }
    
    
    std::shared_ptr<Engine::VertexBuffer> cubesVB;
    std::shared_ptr<Engine::IndexBuffer> cubesIB;
        
    cubesVA.reset(Engine::VertexArray::Create());

    cubesVB.reset(Engine::VertexBuffer::Create(vertices, size * 3 * sizeof(r32)));
    
    Engine::BufferLayout layout = { { Engine::ShaderDataType::Float3, "position" } };
    cubesVB->SetLayout(layout);

    cubesVA->AddVertexBuffer(cubesVB);

    cubesIB.reset(Engine::IndexBuffer::Create(indices, size));
    cubesVA->SetIndexBuffer(cubesIB);  

    delete[] indices;
    delete[] vertices;
}


void MazeLayer::initAvatar()
{
    
    int size = 6 * sectorCount * (stackCount - 2) + 3 * sectorCount * 2;

    glm::vec3 * avatarVertices = new glm::vec3[size];

    glm::vec3 offset = glm::vec3(0.5f, 0.5f, 0.5f) + glm::vec3(avatarPos[0], avatarPos[2], avatarPos[1]);

    float thPerSector = 2 * PI / sectorCount;
    float phiPerStack = PI / stackCount;

    size_t ct = 0;
    for (int i = 0; i < stackCount; i++) {
        float phi = PI / 2 - i * phiPerStack;
        float nphi = PI / 2 - (i + 1) * phiPerStack;
        for (int j = 0; j < sectorCount; j++) {
            float theta = j * thPerSector;
            float ntheta = (j + 1) * thPerSector;

            if (i > 0 && i < (stackCount - 1)) {
                avatarVertices[ct]   = glm::vec3(0.5f*cos(phi) * cos(theta),
                                                 0.5f*sin(phi),
                                                 0.5f*cos(phi) * sin(theta)) + offset;
                avatarVertices[ct+1] = glm::vec3(0.5f*cos(phi) * cos(ntheta),
                                                 0.5f*sin(phi),
                                                 0.5f*cos(phi) * sin(ntheta)) + offset;
                avatarVertices[ct+2] = glm::vec3(0.5f*cos(nphi) * cos(theta),
                                                 0.5f*sin(nphi),
                                                 0.5f*cos(nphi) * sin(theta)) + offset;
                avatarVertices[ct+3] = glm::vec3(0.5f*cos(nphi) * cos(ntheta),
                                                 0.5f*sin(nphi),
                                                 0.5f*cos(nphi) * sin(ntheta)) + offset;
                avatarVertices[ct+4] = glm::vec3(0.5f*cos(phi) * cos(ntheta),
                                                 0.5f*sin(phi),
                                                 0.5f*cos(phi) * sin(ntheta)) + offset;
                avatarVertices[ct+5] = glm::vec3(0.5f*cos(nphi) * cos(theta),
                                                 0.5f*sin(nphi),
                                                 0.5f*cos(nphi) * sin(theta)) + offset;
                ct += 6;
            } else if (i == 0) {
                avatarVertices[ct]   = glm::vec3(0.5f*cos(phi) * cos(theta),
                                                 0.5f*sin(phi),
                                                 0.5f*cos(phi) * sin(theta)) + offset;
                avatarVertices[ct+1] = glm::vec3(0.5f*cos(nphi) * cos(theta),
                                                 0.5f*sin(nphi),
                                                 0.5f*cos(nphi) * sin(theta)) + offset;
                avatarVertices[ct+2] = glm::vec3(0.5f*cos(nphi) * cos(ntheta),
                                                 0.5f*sin(nphi),
                                                 0.5f*cos(nphi) * sin(ntheta)) + offset;
                ct += 3;
            } else {
                avatarVertices[ct]   = glm::vec3(0.5f*cos(phi) * cos(theta),
                                                 0.5f*sin(phi),
                                                 0.5f*cos(phi) * sin(theta)) + offset;
                avatarVertices[ct+1] = glm::vec3(0.5f*cos(phi) * cos(ntheta),
                                                 0.5f*sin(phi),
                                                 0.5f*cos(nphi) * sin(ntheta)) + offset;
                avatarVertices[ct+2] = glm::vec3(0.5f*cos(nphi) * cos(theta),
                                                 0.5f*sin(nphi),
                                                 0.5f*cos(nphi) * sin(theta)) + offset;
                ct += 3;
            }
        }
    }

    u32  * indices = new u32[size];
    r32 * vertices = new r32[size * 3];
    
    for (u32 iter = 0, index = 0; iter < size; iter++, index += 3)
    {
        glm::vec3 v = avatarVertices[iter];
        vertices[index] = v.x;
        vertices[index + 1] = v.y;
        vertices[index + 2] = v.z;
        indices[iter] = iter;
    }

    std::shared_ptr<Engine::VertexBuffer> avatarVB;
    std::shared_ptr<Engine::IndexBuffer> avatarIB;
    
    avatarVA.reset(Engine::VertexArray::Create());    

    avatarVB.reset(Engine::VertexBuffer::Create(vertices, size * 3 * sizeof(r32)));
    Engine::BufferLayout layout = { { Engine::ShaderDataType::Float3, "position" } };
    avatarVB->SetLayout(layout);
    
    avatarVA->AddVertexBuffer(avatarVB);

    avatarIB.reset(Engine::IndexBuffer::Create(indices, size));
    avatarVA->SetIndexBuffer(avatarIB);

    delete[] avatarVertices;
    delete[] indices;
    delete[] vertices;
}

void MazeLayer::initFloor()
{
    
    r32 floorVertices[6 * 3] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, DIM,
        DIM, 0.0f, 0.0f,
        DIM, 0.0f, DIM,
        0.0f, 0.0f, DIM,
        DIM, 0.0f, 0.0f         
    };

    std::shared_ptr<Engine::VertexBuffer> floorVB;
    std::shared_ptr<Engine::IndexBuffer> floorIB;
    
    floorVA.reset(Engine::VertexArray::Create());
    floorVB.reset(Engine::VertexBuffer::Create(floorVertices, sizeof(floorVertices)));
    Engine::BufferLayout floorLayout = { {Engine::ShaderDataType::Float3, "position"} };
    floorVB->SetLayout(floorLayout);
    floorVA->AddVertexBuffer(floorVB);

    u32 indices[6] = {0, 1, 2, 3, 4, 5};
    floorIB.reset(Engine::IndexBuffer::Create(indices, 6));
    floorVA->SetIndexBuffer(floorIB);
    
}

void MazeLayer::resetGridStates()
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
    current_col = 0;
    last_col = -1;        
    avatarPos[0] = 0.0f;
    avatarPos[1] = 0.0f;
    avatarPos[2] = 0.0f;
    m->reset();    
    mouseButtonActive = false;
    initGrid();
    initFloor();
    initCubes();
    initAvatar();
    rotation = 0.0f;
    scaleSize = 1.0f;
    persistence = 0.0f;
    cubeHeight = 1.0f;
}

void MazeLayer::findStartPoint()
{
    avatarPos[0] = 0;
    avatarPos[1] = 0;
    avatarPos[2] = 0;
            
    for (int y = 0; y < m->getDim(); y++) {
        if (m->getValue(0, y) == 0) {
            avatarPos[1] = y;
        }
    }
}


void MazeLayer::OnUpdate(Engine::TimeStep timeStep)
{
    
    if (!mouseButtonActive) rotation += persistence;
    cubeHeight = glm::clamp(cubeHeight, 0.0f, 2.8f);


    // NOTE: DrawCalls
    
    Engine::RenderCommand::SetClearColor({.1f, .1f, .1f, 1});
    Engine::RenderCommand::Clear();
    Engine::RenderCommand::EnableDepthTest();

    glm::vec3 axis(0.0f, 1.0f, 0.0f);
    // Create a global transformation for the model (centre it).
    glm::mat4 W(1.0f);
    W = glm::rotate(W, rotation, axis);
    W = glm::translate( W, glm::vec3( -float(DIM)/2.0f, 0, -float(DIM)/2.0f ) );

    view = glm::lookAt( 
        glm::vec3( 0.0f, 2.*float(DIM)*2.0*M_SQRT1_2 + scaleSize, float(DIM)*2.0*M_SQRT1_2  ),
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 0.0f, 1.0f, 0.0f ) );

    
    camera.SetViewMatrix(view);
    
    Engine::Renderer::BeginScene(camera, W);

    Engine::Renderer::DrawTypeTriangles();
    Engine::Renderer::Submit(shader, floorVA, glm::vec3(colorF[0], colorF[1], colorF[2]));
    Engine::Renderer::Submit(shader, avatarVA, glm::vec3(colorA[0], colorA[1], colorA[2]));    
    Engine::Renderer::Submit(shader, cubesVA, glm::vec3(colorW[0], colorW[1], colorW[2]));

    Engine::Renderer::DrawTypeLines();
    Engine::Renderer::Submit(shader, gridVA, glm::vec3(1.0f, 1.0f, 1.0f));
    
    Engine::Renderer::EndScene();

    
}

static bool showDebugWindow(true);

void MazeLayer::OnImGuiRender()
{
    // We already know there's only going to be one window, so for 
    // simplicity we'll store button states in static local variables.
    // If there was ever a possibility of having multiple instances of
    // A1 running simultaneously, this would break; you'd want to make
    // this into instance fields of A1.
    // ImGui::ShowDemoWindow();

    float opacity(0.5f);
    ImGui::SetNextWindowBgAlpha(opacity);
        
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Windows")) {
            ImGui::MenuItem("Debug Window", NULL, &showDebugWindow);            
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (showDebugWindow)
    {
                
        ImGui::Begin("Debug Window", &showDebugWindow);

        if(ImGui::CollapsingHeader("Application"))
        {
        
            if( ImGui::Button( "Quit Application (Q)" ) ) {
                Engine::Application::Get().Quit();
            }

            if( ImGui::Button( "Dig (D)" ) ) {
                m->digMaze();
                m->printMaze();
                findStartPoint();        
                initCubes();
                initAvatar();
            }

            if ( ImGui::Button( "Reset (R)" ) ) {
                resetGridStates();
            }
        }
        // Eventually you'll create multiple color widgets with
        // radio buttons.  If you use PushID/PopID to give them all
        // unique IDs, then ImGui will be able to keep them separate.
        // This is unnecessary with a single color selector and
        // radio button, but I'm leaving it in as an example.

        // Prefixing a widget name with "##" keeps it from being
        // displayed.

        if(ImGui::CollapsingHeader("Maze Edit"))
        {
            
            ImGui::PushID( "radio" );
            ImGui::RadioButton( "Floor##Col", &current_col, 0 );
            ImGui::SameLine();
            ImGui::RadioButton( "Wall##Col", &current_col, 1 );
            ImGui::SameLine();
            ImGui::RadioButton( "Avatar##Col", &current_col, 2);
            ImGui::PopID();
    
            if (current_col != last_col) {
                if (current_col == 0) {
                    widgetColor[0] = colorF[0];
                    widgetColor[1] = colorF[1];
                    widgetColor[2] = colorF[2];
                }

                if (current_col == 1) {
                    widgetColor[0] = colorW[0];
                    widgetColor[1] = colorW[1];
                    widgetColor[2] = colorW[2];
                }

                if (current_col == 2) {
                    widgetColor[0] = colorA[0];
                    widgetColor[1] = colorA[1];
                    widgetColor[2] = colorA[2];
                }
            }    
    
            ImGui::PushID( 0 );
            ImGui::ColorEdit3( "##Color", widgetColor );
            ImGui::PopID();
        
            if (current_col == 0) {
                colorF[0] = widgetColor[0];
                colorF[1] = widgetColor[1];
                colorF[2] = widgetColor[2];
            }

            if (current_col == 1) {
                colorW[0] = widgetColor[0];
                colorW[1] = widgetColor[1];
                colorW[2] = widgetColor[2];
            }

            if (current_col == 2) {
                colorA[0] = widgetColor[0];
                colorA[1] = widgetColor[1];
                colorA[2] = widgetColor[2];
            }
    
            last_col = current_col;
        }

        if(ImGui::CollapsingHeader("Controls"))
        {
            ImGui::SliderFloat("Zoom Speed", &zoomSpeed, 0.0f, 10.0f, "ratio = %.3f");
            ImGui::SliderFloat("Rotation Speed", &rotateSpeed, 0.0f, 1.0f, "ratio = %.3f");
            ImGui::SliderFloat("Persistence Speed", &persistSpeed, 0.0f, 1.0f, "ratio = %.3f");
        }

        ImGui::SeparatorText("Performance:");
        ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );
        ImGui::End();
    }

}

void MazeLayer::OnEvent(Engine::Event& event)
{
    Engine::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Engine::MouseMovedEvent>(BIND_EVENT_FUNCTION(MazeLayer::OnMouseMoveEvent));
    dispatcher.Dispatch<Engine::MousePressedEvent>(BIND_EVENT_FUNCTION(MazeLayer::OnMousePressedEvent));
    dispatcher.Dispatch<Engine::MouseReleasedEvent>(BIND_EVENT_FUNCTION(MazeLayer::OnMouseReleaseEvent));
    dispatcher.Dispatch<Engine::MouseScrolledEvent>(BIND_EVENT_FUNCTION(MazeLayer::OnMouseScrollEvent));
    dispatcher.Dispatch<Engine::KeyPressedEvent>(BIND_EVENT_FUNCTION(MazeLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<Engine::KeyReleasedEvent>(BIND_EVENT_FUNCTION(MazeLayer::OnKeyReleaseEvent));

}

bool MazeLayer::noWall(int x, int y)
{
    bool result = x == -1 || y == -1 || x == DIM || y == DIM || !m->getValue(x, y);
    return result;
}

bool MazeLayer::OnMouseMoveEvent(Engine::MouseMovedEvent & event)
{
    
    if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
        // Put some code here to handle rotations.  Probably need to
        // check whether we're *dragging*, not just moving the mouse.
        // Probably need some instance variables to track the current
        // rotation amount, and maybe the previous X position (so 
        // that you can rotate relative to the *change* in X.
        deltaX = (r32)(event.GetX() - xPrev);
        if (mouseButtonActive && (deltaX * deltaX) > 1) {
            ENGINE_TRACE("deltaX: {0}", deltaX);
            rotation += deltaX * rotateSpeed * 0.01f;
            persistence = deltaX * persistSpeed * 0.001f;
        }
    }

    xPrev = event.GetX();
    return false;
}

bool MazeLayer::OnMousePressedEvent(Engine::MousePressedEvent & event)
{
    if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
        // The user clicked in the window.  If it's the left
        // mouse button, initiate a rotation.
        mouseButtonActive = true;
        persistence = 0.0f;
            
    }
    return false;
}

bool MazeLayer::OnMouseReleaseEvent(Engine::MouseReleasedEvent & event)
{
    mouseButtonActive = false;
    return false;
}

bool MazeLayer::OnMouseScrollEvent(Engine::MouseScrolledEvent & event)
{
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) return false;
    
    // Zoom in or out.
    if (event.GetOffsetY() == -1) {
        scaleSize -= zoomSpeed;
    } else if (event.GetOffsetY() == 1) {
        scaleSize += zoomSpeed;
    }
    
    return false;
}

bool MazeLayer::OnKeyPressedEvent(Engine::KeyPressedEvent & event)
{

    bool canMove = !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow); 
   
    i32 keyCode = event.GetKeyCode();

    switch (keyCode)
    {
        // Respond to some key events.
        case E_KEY_Q: {
            // cout << "Q key pressed" << endl;
            Engine::Application::Get().Quit();
            break;
        }
            
        case E_KEY_D: {
            m->digMaze();
            findStartPoint();        
            initCubes();
            initAvatar();
            break;
        }

        case E_KEY_R: {
            resetGridStates();
            break;
        }

        case E_KEY_SPACE: {
            cubeHeight += 0.2f;
            initCubes();
            break;
        }

        case E_KEY_BACKSPACE: {
            cubeHeight -= 0.2f;
            initCubes();
            break;
        }

        case E_KEY_LEFT: {
            if ((avatarPos[0] > -1) && canMove)
            {
                if (noWall(avatarPos[0] - 1, avatarPos[1])) {
                    avatarPos[0] -= 1;
                    initAvatar();
                } else if (event.GetMods() == E_MOD_SHIFT) {
                    avatarPos[0] -= 1;
                    m->setValue( avatarPos[0], avatarPos[1], 0 );
                    initCubes();
                    initAvatar();
                }
            }
            break;
        }
        
        case E_KEY_RIGHT: {

            if ((avatarPos[0] < DIM || avatarPos[0] == -1) && canMove)
            {
                if (noWall(avatarPos[0] + 1, avatarPos[1])) {
                    avatarPos[0] += 1;
                    initAvatar();
                } else if (event.GetMods() == E_MOD_SHIFT) {
                    avatarPos[0] += 1;
                    m->setValue( avatarPos[0], avatarPos[1], 0 );
                    initCubes();
                    initAvatar();
                }
            }
            break;
        }
        
        case E_KEY_UP: {

            if ((avatarPos[1] > -1) && canMove)
            {
                if (noWall(avatarPos[0], avatarPos[1] - 1))
                {
                    avatarPos[1] -= 1;
                    initAvatar();
                } else if (event.GetMods() == E_MOD_SHIFT) {
                    avatarPos[1] -= 1;
                    m->setValue( avatarPos[0], avatarPos[1], 0 );
                    initCubes();
                    initAvatar();
                }
            }
            break;
        }
        
        case E_KEY_DOWN: {

            if ((avatarPos[1] < DIM || avatarPos[1] == -1) && canMove)
            {
                if (noWall(avatarPos[0], avatarPos[1] + 1))
                {
                    avatarPos[1] += 1;
                    initAvatar();
                } else if (event.GetMods() == E_MOD_SHIFT) {
                    avatarPos[1] += 1;
                    m->setValue( avatarPos[0], avatarPos[1], 0 );
                    initCubes();
                    initAvatar();
                }
            }
            break;
        }        

    }
    
    return false;
}

bool MazeLayer::OnKeyReleaseEvent(Engine::KeyReleasedEvent & event)
{
    return false;
}



Engine::Application * Engine::CreateApplication()
{
    return new SandBox();
}
