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

#include <shader/Shader.hpp>
#include <shader/ShaderProgram.hpp>
#include <Texture.hpp>
#include <Logger.hpp>
#include <Camera.hpp>

// global variables
constexpr auto WINDOW_HEIGHT = 480.0f;
constexpr auto WINDOW_WIDTH = 640.0f;
// camera
GLTool::Camera cam(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));
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

void processInput(GLFWwindow *window, GLTool::Camera &cam, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        lineMode = !lineMode;
        glPolygonMode(GL_FRONT_AND_BACK, lineMode ? GL_LINE : GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.processInput(GLTool::Camera::Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.processInput(GLTool::Camera::Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.processInput(GLTool::Camera::Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.processInput(GLTool::Camera::Movement::RIGHT, deltaTime);

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

void instantiateScene() {
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
	glGenVertexArrays(1, &colorVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(colorVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the vertex attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
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
        { GL_VERTEX_SHADER, "shaders/color.vert" },
        { GL_FRAGMENT_SHADER, "shaders/color.frag" },
    });
    ShaderProgram lightingShader({
        {GL_VERTEX_SHADER, "shaders/lighting.vert"},
        {GL_FRAGMENT_SHADER, "shaders/lighting.frag"},
    });

    if (!lightingShader.ready() || !colorShader.ready()) {
        std::cerr << "Cannot setup shaders" << std::endl;
        return clear(1);
    }
    instantiateScene();
    GLTool::Texture diffuseMap("ressources/container2.png", GL_TEXTURE_2D, GL_RGBA, GL_RGBA, false);
    GLTool::Texture specularDiffuseMap("ressources/container2_specular.png", GL_TEXTURE_2D, GL_RGBA, GL_RGBA, false);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    std::array<glm::vec3, 4> pointLightPositions = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    const float lightRadius = 1.5f;

    colorShader.use();
    // object material
    colorShader.setUniform("material.diffuse", 0);
    colorShader.setUniform("material.specular", 1);
    colorShader.setUniform("material.shininess", 32.f);

    glClearColor(0.0,0.0,0.0,0);
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
        colorShader.setVec("dirLight.direction", -0.2f, -1.0f, -0.3f);
        colorShader.setVec("dirLight.ambient", 0.0f, 0.1f, 0.1f);
        colorShader.setVec("dirLight.diffuse", 0.0f, 0.0f, 0.0f);
        colorShader.setVec("dirLight.specular", 0.0f, 0.0f, 0.0f);

        glm::vec3 pointLightColor(static_cast<float>(glm::abs(cos(glfwGetTime()))) * glm::vec3(0.0f, 1.0f, 0.2f));
        glm::vec3 pointDiffuseColor = pointLightColor   * glm::vec3(0.8f);
        glm::vec3 pointAmbientColor = pointLightColor * glm::vec3(0.1f);
        for (int i = 0; i < pointLightPositions.size(); i++) {
            std::string idx = std::to_string(i);
            colorShader.setVec(("pointLights[" + idx + "].position").c_str(), pointLightPositions[i]);
            colorShader.setVec(("pointLights[" + idx + "].ambient").c_str(), pointAmbientColor);
            colorShader.setVec(("pointLights[" + idx + "].diffuse").c_str(), pointDiffuseColor);
            colorShader.setVec(("pointLights[" + idx + "].specular").c_str(), pointLightColor);
            colorShader.setUniform(("pointLights[" + idx + "].constant").c_str(), 1.0f);
            colorShader.setUniform(("pointLights[" + idx + "].linear").c_str(), 0.09f);
            colorShader.setUniform(("pointLights[" + idx + "].quadratic").c_str(), 0.032f);
        }

        // spot light
        glm::vec3 spotLightColor(1.0f, 0.0f, 0.0f);
        glm::vec3 spotDiffuseColor = spotLightColor   * glm::vec3(0.8f);
        glm::vec3 spotAmbientColor = spotLightColor * glm::vec3(0.1f);
        colorShader.setVec("spotLight.position", cam.position());
        colorShader.setVec("spotLight.direction", cam.front());
        colorShader.setUniform("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        colorShader.setUniform("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        colorShader.setVec("spotLight.ambient", spotAmbientColor);
        colorShader.setVec("spotLight.diffuse", spotDiffuseColor);
        colorShader.setVec("spotLight.specular", spotLightColor);
        colorShader.setUniform("spotLight.constant",  1.0f);
        colorShader.setUniform("spotLight.linear",    0.09f);
        colorShader.setUniform("spotLight.quadratic", 0.032f);	

        diffuseMap.activate(GL_TEXTURE0);
        specularDiffuseMap.activate(GL_TEXTURE1);

        glBindVertexArray(colorVAO);
        for(unsigned int i = 0; i < 10; i++)
        {
            // MVP matrix
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            colorShader.setMat("model", model);
            colorShader.setMat("view", view);
            colorShader.setMat("projection", projection);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // light
        glBindVertexArray(lightVAO);
        lightingShader.use();
        for (auto &pointLightPos : pointLightPositions) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPos);
            model = glm::scale(model, glm::vec3(0.2f)); 

            lightingShader.setMat("model", model);
            lightingShader.setMat("view", view);
            lightingShader.setMat("projection", projection);
            lightingShader.setVec("lightColor", pointLightColor);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


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