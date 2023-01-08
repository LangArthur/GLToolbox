#pragma once

#include <math.h>

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GLTool
{

    class Camera
    {
        public:
            /**
             * @brief encapsulation of keyboard event
             */
            // TODO: add up and down
            enum Movement {
                FORWARD, BACKWARD, LEFT, RIGHT
            };

            /**
             * @brief Construct a new Camera object.
             * @param cameraPos position of the camera in te world.
             * @param cameraFront front of the camera.
             * @param cameraUp up of the camera.
             */
            Camera(const glm::vec3 &cameraPos, const glm::vec3 cameraFront, const glm::vec3 cameraUp);
            ~Camera() = default;

            /**
             * @brief Get the view matrix.
             * @return glm::mat4 view matrix.
             */
            inline glm::mat4 getViewMat() const {
                return glm::lookAt(m_pos, m_pos + m_front, m_up);
            };

            inline float fov() const {
                return m_fov;
            }

            inline glm::vec3 position() const {
                return m_pos;
            }

            inline glm::vec3 front() const {
                return m_front;
            }

            /**
             * @brief process input from a keyboard.
             * @param mov movement of the camera.
             * @param deltaTime time taken to render the previous frame.
             */
            void processInput(Movement mov, float deltaTime);
            /**
             * @brief process mouse input to rotate the camera.
             * @param xOffset x offset of the mouse.
             * @param yOffset y offset of the mouse.
             * @param constrainPitch constrain the pitch to avoid screen flipping.
             */
            void processMouse(float xOffset, float yOffset, bool constrainPitch = true);
            /**
             * @brief process scroll input to zoom in / out the camera.
             * @param yOffset y offset of the scroll.
             */
            void processScroll(float yOffset);

        private:
            /* update front, up and right when pitch or yawn has been change */
            void updateCamVectors();

            /* position of the camera in the world */
            glm::vec3 m_pos;
            /* direction vector (in which direction the camera look at) */
            glm::vec3 m_front;
            /* camera y-axis */
            glm::vec3 m_up;
            /* camera x-axis */
            glm::vec3 m_right;
            /* world y-axis */
            glm::vec3 m_worldUp;

            // euler angles
            float m_yaw = -90.0f;
            float m_pitch = 0.0f;

            // cam options
            /* filed of view (used as a zoom) */
            float m_fov = 45.0f;
            /* sensibility of the mouse when rotating */
            float m_mouseSensibility = 0.05f;
            /* speed of the camera when moving*/
            float m_speed = 5.0f;
    };    
} // namespace GLTool
