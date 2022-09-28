#include "shader/Shader.hpp"

int main(int argc, char const **argv)
{
    Shader(GL_VERTEX_SHADER, "../shaders/SimpleVertexShader.vert");
    Shader(GL_FRAGMENT_SHADER, "../shaders/SimpleFragmentShader.frag");

    return 0;
}
