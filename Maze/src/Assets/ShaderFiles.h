#if !defined(SHADERFILES_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <string>

namespace ShaderFiles
{
    
    inline std::string triangleVS =
        R"(
             #version 330

            layout(location = 0) in vec3 position;
            layout(location = 1) in vec4 color;

            uniform mat4 VP;

            out vec4 interpColor;

            void main()
            {
                interpColor = color;
                gl_Position = VP * vec4(position, 1.0);
            }
        )";

    inline std::string triangleFS =
        R"( 
        
            #version 330

            out vec4 fragColor;

            in vec4 interpColor;

            void main()
            {
                fragColor = interpColor;
            }
        
        )";

    inline std::string blueSquareVS =
        R"(
            #version 330

            layout(location = 0) in vec3 position;

            uniform mat4 VP;

            void main()
            {
                gl_Position = VP * vec4(position, 1.0);
            } 
        )";

    inline std::string blueSquareFS =
        R"(
            #version 330


            out vec4 fragColor;

            void main()
            {
                fragColor = vec4(0.2, 0.2, 0.7, 1.0);
            }
        
        )";

    inline std::string mazeVS =
        R"(

            #version 330

            uniform mat4 VP;
            uniform mat4 M;
            in vec3 position;

            void main() {
              gl_Position = VP * M * vec4(position, 1.0);
            })";

    inline std::string mazeFS =
        R"(

          #version 330

          uniform vec3 color;

          out vec4 fragColor;

          void main() {
            fragColor = vec4( color, 1 );
          })";
    
}

#define SHADERFILES_H
#endif
