/**
 * @file test_shader.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief test Shader object
 * @date 2022-08-29
 */

#include <gtest/gtest.h>

#include "shader/Shader.hpp"

class ShaderTest : public testing::Test
{};

TEST_F(ShaderTest, compileTest) {
    GLTools::Shader(GL_VERTEX_SHADER, "../shaders/SimpleVertexShader.vert");
}