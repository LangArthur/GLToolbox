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
	glGenVertexArrays(1, &colorVAO);
	glBindVertexArray(colorVAO);


    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

	GLuint VBO; // Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the vertex attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
    instantiateScene();

    glm::vec3 cubePositions = glm::vec3( 0.0f,  0.0f,  0.0f);
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    glUseProgram(colorShader.id());
    colorShader.setVec3<float>("objectColor", 1.0f, 0.5f, 0.31f);
    colorShader.setVec3<float>("lightColor", 1.0f, 1.0f, 1.0f);    

    glClearColor(0.1,0.1,0.1,0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallBack);
    glfwSetScrollCallback(window, scroll_callback); 
    // time variables
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 view = cam.getViewMat();
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(cam.fov()), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

        // colored cube
        glUseProgram(colorShader.id());
        glBindVertexArray(colorVAO);

        // MVP matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));  

        unsigned int transformLoc = glGetUniformLocation(colorShader.id(), "model");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
        transformLoc = glGetUniformLocation(colorShader.id(), "view");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));
        transformLoc = glGetUniformLocation(colorShader.id(), "projection");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // light
        glUseProgram(lightingShader.id());
        glBindVertexArray(lightVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); 
        transformLoc = glGetUniformLocation(lightingShader.id(), "model");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
        transformLoc = glGetUniformLocation(lightingShader.id(), "view");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));
        transformLoc = glGetUniformLocation(lightingShader.id(), "projection");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        processInput(window, cam, deltaTime);
        /* Poll for and process events */
        glfwPollEvents();
    }
    return clear(0);
}