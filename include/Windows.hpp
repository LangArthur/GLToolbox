/**
 * @file Windows.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief GLFW Windows encapsulation declaration
 * @date 2023-05-06
 */

#pragma once

#include <stdexcept>
#include <memory>
#include <functional>

#include <GLFW/glfw3.h>

#include "OpenGLVersion.hpp"

namespace GLTools
{
    class Window
    {
        using MoveMouseCallBack = std::function<void(double, double)>;
        using ScrollCallback = std::function<void(double, double)>;

        struct windowDestroyer {
            void operator()(GLFWwindow* ptr){
                glfwDestroyWindow(ptr);
            }
        };
        using UniqueWindow = std::unique_ptr<GLFWwindow, windowDestroyer>;

       public:
            Window(int width, int height, const char *title, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);
            ~Window() = default;

            // TODO: this method should not exist
            inline GLFWwindow *data()
            {
                return m_window.get();
            }

            inline void enableCursor(bool state)
            {
                glfwSetInputMode(m_window.get(), GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
            }

            void update();
            void close();

            // TODO: find a more generic way to handle callbacks
            void registerMoveMouseCallBack(MoveMouseCallBack cb);
            void registerScrollCallBack(ScrollCallback cb);

        private:
            UniqueWindow m_window;
            MoveMouseCallBack m_moveMouseCallBack;
            ScrollCallback m_scrollCallBack;

    };
} /* GLTools namespace */
