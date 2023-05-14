/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @date 2022-06-20
 */

#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// debugging mat
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/string_cast.hpp>

#include <assimp/Importer.hpp>

#include "Windows.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "lights/PointLight.hpp"
#include "Model.hpp"

// global variables
constexpr auto WINDOW_HEIGHT = 480.0f;
constexpr auto WINDOW_WIDTH = 640.0f;

GLTools::Camera cam(glm::vec3(-0.5f, -0.5f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
// GLTools::Camera cam(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));

// fly camera callbacks;
void mouseCallBack(GLFWwindow *window, double xPos, double yPos)
{
    static float lastX = WINDOW_WIDTH / 2;
    static float lastY = WINDOW_HEIGHT / 2;
    static bool alreadyCalled = false;

    if (!alreadyCalled)
    {
        lastX = xPos;
        lastY = yPos;
        alreadyCalled = true;
    }
    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; // reversed since y-coordinates range from bottom to top
    cam.processMouse(xOffset, yOffset);
    lastX = xPos;
    lastY = yPos;
};

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    cam.processScroll(yOffset);
}

void processInput(GLTools::Window &window, GLTools::Camera &cam, float deltaTime)
{
    if (glfwGetKey(window.data(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        window.close();
    }
    if (glfwGetKey(window.data(), GLFW_KEY_W) == GLFW_PRESS)
    {
        cam.processInput(GLTools::Camera::Movement::FORWARD, deltaTime);
    }
    if (glfwGetKey(window.data(), GLFW_KEY_S) == GLFW_PRESS)
    {
        cam.processInput(GLTools::Camera::Movement::BACKWARD, deltaTime);
    }
    if (glfwGetKey(window.data(), GLFW_KEY_A) == GLFW_PRESS)
    {
        cam.processInput(GLTools::Camera::Movement::LEFT, deltaTime);
    }
    if (glfwGetKey(window.data(), GLFW_KEY_D) == GLFW_PRESS)
    {
        cam.processInput(GLTools::Camera::Movement::RIGHT, deltaTime);
    }
}

int clear(int status)
{
    glfwTerminate();
    return status;
}

std::array<GLTools::Mesh, 2> instantiateScene()
{
    std::vector<GLTools::Vertex> vertices = {
        { {-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f} },
        { {0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f} },
        { {0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f} },
        { {-0.5f, 0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f} },

        { {-0.5f, -0.5f,  0.5f}, {0.0f,  0.0f, 1.0f},   {0.0f, 0.0f} },
        { {0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},   {1.0f, 0.0f} },
        { {0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},   {1.0f, 1.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.0f,  0.0f, 1.0f},   {0.0f, 1.0f} },

        { {-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f} },
        { {-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f} },

        { {0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f} },
        { {0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f} },
        { {0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f} },
        { {0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f} },

        { {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f} },
        { {0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 1.0f} },
        { {0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 0.0f} },

        { {-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f} },
        { {0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f} },
        { {0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f} },
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
    };
    std::vector<GLTools::Texture> textures;
    GLTools::Texture::LoadingParams textureParams{
        .textureMode = GL_TEXTURE_2D,
        .flipImage = true,
    };
    textures.emplace_back("../resources/container2.png", GLTools::Texture::TextureType::DIFFUSE, textureParams);
    textures.emplace_back("../resources/container2_specular.png", GLTools::Texture::TextureType::SPECULAR, textureParams);

    return std::array<GLTools::Mesh, 2>({
        GLTools::Mesh(vertices, indices, textures),
        GLTools::Mesh(vertices, indices, {}),
    });
}

int main(int argc, char *argv[])
{
    GLTools::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Chap 2");
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to init glew");
    }
    window.enableCursor(false);
    glfwSetCursorPosCallback(window.data(), mouseCallBack);
    glfwSetScrollCallback(window.data(), scrollCallback);

    glEnable(GL_DEPTH_TEST);
    // shaders
    ShaderProgram colorShader({
        {GL_VERTEX_SHADER, "../shaders/color.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/color.frag"},
    });
    ShaderProgram lightShader({
        {GL_VERTEX_SHADER, "../shaders/lighting.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/lighting.frag"},
    });

    if (!colorShader.ready())
    {
        std::cerr << "Cannot setup shaders" << std::endl;
        return clear(1);
    }

    auto [cube, light] = instantiateScene();
    GLTools::Model backPack("../resources/backpack/backpack.obj");
    glm::vec3 backPackPos = {0.0f, 0.0f, 0.0f};

    auto pointLightPosition = glm::vec3(0.0f, 0.0f, 1.0f);
    GLTools::PointLight pointLight;
    pointLight.position = pointLightPosition;
    pointLight.constant = 1.0f;
    pointLight.linear = 0.09f;
    pointLight.quadratic = 0.032f;

    glClearColor(0.1, 0.1, 0.1, 0);
    // time variables
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    glm::vec3 cubePos = {0.0f, 0.0f, 0.0f};
    colorShader.use();
    colorShader.setUniform("material.shininess", 32.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.data()))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, cam, deltaTime);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        colorShader.use();
        /* Backpack */
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, backPackPos);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 view = cam.getViewMat();
        glm::mat4 projection = glm::perspective(glm::radians(cam.fov()), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

        pointLight.position.x = pointLightPosition.x + glm::cos((float)glfwGetTime());
        pointLight.position.y = pointLightPosition.y + glm::sin((float)glfwGetTime());
        glm::vec3 pointLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
        pointLight.diffuse = pointLightColor * glm::vec3(0.7f);
        pointLight.ambient = pointLightColor * glm::vec3(0.1f);
        pointLight.specular = pointLightColor * glm::vec3(0.5f, 0.5f, 0.5f);
        pointLight.render(colorShader, "pointLights[" + std::to_string(0) + "]");

        colorShader.setMat("model", model);
        colorShader.setMat("view", view);
        colorShader.setMat("projection", projection);
        colorShader.setVec("viewPos", cam.position());
        backPack.draw(colorShader);


        /* Light */
        lightShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLight.position);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat("model", model);
        lightShader.setMat("view", view);
        lightShader.setMat("projection", projection);
        lightShader.setVec("lightColor", pointLightColor);
        light.draw(lightShader);
        window.update();
    }
    return clear(0);
}