/**
 * @file Window.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Window implementation
 * @date 2023-05-06
 */

#include "Windows.hpp"

namespace GLTools {
	static bool s_GLFWInitialized = false;

    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Window::Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
        // init glfw
        if (!s_GLFWInitialized) {
            if (!glfwInit()) {
                throw std::runtime_error("Failed to instantiate glfw");
            }
            s_GLFWInitialized = true;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenglVersion::MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenglVersion::MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = std::unique_ptr<GLFWwindow, windowDestroyer>(glfwCreateWindow(width, height, title, monitor, share));
        if (!m_window) {
            throw std::runtime_error("Failed to create the window");
        }
        glViewport(0, 0, width, height);
        glfwMakeContextCurrent(m_window.get());
        glfwSetFramebufferSizeCallback(m_window.get(), framebufferSizeCallback);
        glfwSetWindowUserPointer(m_window.get(), this);
    }

    void Window::close() {
        glfwSetWindowShouldClose(m_window.get(), true);
    }

    void Window::update() {
        glfwSwapBuffers(m_window.get());
        glfwPollEvents();
    }

    void Window::registerMoveMouseCallBack(MoveMouseCallBack cb) {
        m_moveMouseCallBack = std::move(cb);
        glfwSetCursorPosCallback(m_window.get(), [](GLFWwindow* window, double xPos, double yPos) {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            self.m_moveMouseCallBack(xPos, yPos);
        });
    }

    void Window::registerScrollCallBack(ScrollCallback cb) {
        m_scrollCallBack = std::move(cb);
        glfwSetCursorPosCallback(m_window.get(), [](GLFWwindow* window, double xPos, double yPos) {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            self.m_scrollCallBack(xPos, yPos);
        });
    }

}