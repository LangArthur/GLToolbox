/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-06-20
 */

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// debugging mat
#include <glm/gtx/string_cast.hpp>
#include <assimp/Importer.hpp>

#include "shader/Shader.hpp"
#include "shader/ShaderProgram.hpp"
#include "Texture.hpp"
#include "Logger.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "lights/DirectionalLight.hpp"

// global variables
constexpr auto WINDOW_HEIGHT = 480.0f;
constexpr auto WINDOW_WIDTH = 640.0f;
// camera
GLTools::Camera cam(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));
// polygon mode
bool lineMode = false;
// texture blending ratio
float ratio = 0.2f;

GLuint colorVAO;
GLuint lightVAO;
GLuint VBO; // Vertex Buffer Object

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, GLTools::Camera &cam, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        lineMode = !lineMode;
        glPolygonMode(GL_FRONT_AND_BACK, lineMode ? GL_LINE : GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.processInput(GLTools::Camera::Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.processInput(GLTools::Camera::Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.processInput(GLTools::Camera::Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.processInput(GLTools::Camera::Movement::RIGHT, deltaTime);

}

void mouseCallBack(GLFWwindow* window, double xPos, double yPos) {
    static float lastX = WINDOW_WIDTH / 2;
    static float lastY = WINDOW_HEIGHT / 2;
    static bool alreadyCalled = false;

    if (!alreadyCalled) {
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.processScroll(yoffset);
}

std::array<GLTools::Mesh, 2> instantiateScene() {
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
    GLTools::Texture::LoadingParams textureParams { 
        .textureFormat = GL_RGBA,
        .flipImage = true,
    };
    textures.emplace_back("../ressources/container2.png", GL_TEXTURE_2D, GLTools::Texture::TextureType::DIFFUSE, textureParams);
    textures.emplace_back("../ressources/container2_specular.png", GL_TEXTURE_2D, GLTools::Texture::TextureType::SPECULAR, textureParams);

    return std::array<GLTools::Mesh, 2>({
        GLTools::Mesh(vertices, indices, textures),
        GLTools::Mesh(vertices, indices, {}),
    });
}

GLFWwindow* init(int argc, char **argv) {
    GLFWwindow* window;
    // init glfw
    if (!glfwInit()) {
        std::cerr << "Failed to instantiate glfw\n";
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        std::cerr << "Error: cannot instantiate window." << std::endl;
        return nullptr;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwMakeContextCurrent(window);
    // setup glew
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Cannot init glew library: " << glewGetErrorString(err) << std::endl;
        return nullptr;
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    return window;
    
}

int clear(int status) {
    glfwTerminate();
    return status;
}

int main(int argc, char *argv[])
{
    GLFWwindow* window = init(argc, argv);
    /* Create a windowed mode window and its OpenGL context */
    if (!window)
    {
        return clear(1);
    }
    glm::vec4 vec4;

    glEnable(GL_DEPTH_TEST);
    // shaders
    ShaderProgram colorShader({
        { GL_VERTEX_SHADER, "../shaders/color.vert" },
        { GL_FRAGMENT_SHADER, "../shaders/color.frag" },
    });
    ShaderProgram lightingShader({
        {GL_VERTEX_SHADER, "../shaders/lighting.vert"},
        {GL_FRAGMENT_SHADER, "../shaders/lighting.frag"},
    });

    if (!lightingShader.ready() || !colorShader.ready()) {
        std::cerr << "Cannot setup shaders" << std::endl;
        return clear(1);
    }

    // GLTools::Model backpack("/home/alang/Documents/github_projects/GLToolbox/ressources/backpack/backpack.obj");
    GLTools::Model backpack("../ressources/backpack/backpack.obj");
    auto [container, light] = instantiateScene();

    GLTools::DirectionalLight dirLight("dirLight");
    dirLight.direction = { -0.2f, -1.0f, -0.3f };
    dirLight.ambient = { 0.8f, 0.8f, 0.8f };
    dirLight.diffuse = { 0.0f, 0.0f, 0.0f };
    dirLight.specular = { 0.0f, 0.0f, 0.0f };

    std::array<glm::vec3, 1> pointLightPositions = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        // glm::vec3( 2.3f, -3.3f, -4.0f),
        // glm::vec3(-4.0f,  2.0f, -12.0f),
        // glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    glm::vec3 backPackPos = { 0.0f,  0.0f,  0.0f };
    const float lightRadius = 1.5f;

    glClearColor(0.1, 0.1, 0.1, 0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallBack);
    glfwSetScrollCallback(window, scroll_callback); 
    // time variables
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, cam, deltaTime);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = cam.getViewMat();
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(cam.fov()), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

        colorShader.use();
        // Directional light
        dirLight.render(colorShader);

        glm::vec3 pointLightColor(static_cast<float>(glm::abs(cos(glfwGetTime()))) * glm::vec3(1.0f, 1.0f, 1.0f));
        glm::vec3 pointDiffuseColor = pointLightColor   * glm::vec3(0.8f);
        glm::vec3 pointAmbientColor = pointLightColor * glm::vec3(0.1f);
        // for (int i = 0; i < pointLightPositions.size(); i++) {
        //     std::string idx = std::to_string(i);
        //     colorShader.setVec(("pointLights[" + idx + "].position").c_str(), pointLightPositions[i]);
        //     colorShader.setVec(("pointLights[" + idx + "].ambient").c_str(), pointAmbientColor);
        //     colorShader.setVec(("pointLights[" + idx + "].diffuse").c_str(), pointDiffuseColor);
        //     colorShader.setVec(("pointLights[" + idx + "].specular").c_str(), pointLightColor);
        //     colorShader.setUniform(("pointLights[" + idx + "].constant").c_str(), 1.0f);
        //     colorShader.setUniform(("pointLights[" + idx + "].linear").c_str(), 0.09f);
        //     colorShader.setUniform(("pointLights[" + idx + "].quadratic").c_str(), 0.032f);
        // }

        // spot light
        // glm::vec3 spotLightColor(1.0f, 1.0f, 1.0f);
        // glm::vec3 spotDiffuseColor = spotLightColor   * glm::vec3(0.8f);
        // glm::vec3 spotAmbientColor = spotLightColor * glm::vec3(0.1f);
        // colorShader.setVec("spotLight.position", cam.position());
        // colorShader.setVec("spotLight.direction", cam.front());
        // colorShader.setUniform("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        // colorShader.setUniform("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        // colorShader.setVec("spotLight.ambient", spotAmbientColor);
        // colorShader.setVec("spotLight.diffuse", spotDiffuseColor);
        // colorShader.setVec("spotLight.specular", spotLightColor);
        // colorShader.setUniform("spotLight.constant",  1.0f);
        // colorShader.setUniform("spotLight.linear",    0.09f);
        // colorShader.setUniform("spotLight.quadratic", 0.032f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, backPackPos);
        colorShader.setMat("model", model);
        colorShader.setMat("view", view);
        colorShader.setMat("projection", projection);
        backpack.draw(colorShader);

        // light
        // glBindVertexArray(lightVAO);
        // lightingShader.use();
        // for (auto &pointLightPos : pointLightPositions) {
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, pointLightPos);
        //     model = glm::scale(model, glm::vec3(0.2f)); 

        //     lightingShader.setMat("model", model);
        //     lightingShader.setMat("view", view);
        //     lightingShader.setMat("projection", projection);
        //     lightingShader.setVec("lightColor", pointLightColor);
        //     light.draw(lightingShader);
        // }


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &colorVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    return clear(0);
}