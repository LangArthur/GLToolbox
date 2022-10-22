#include "Camera.hpp"

namespace GLTool
{
    Camera::Camera(const glm::vec3 &cameraPos, const glm::vec3 cameraFront, const glm::vec3 cameraUp)
        : m_pos(cameraPos), m_front(cameraFront), m_up(cameraUp)
    { }

    Camera::~Camera()
    { }

    void Camera::processInput(const CamMovement &mov, float deltaTime) {
        const float cameraSpeed = m_speed * deltaTime;
        switch (mov)
        {
            case FORWARD:
                m_pos += m_front * cameraSpeed;
                break;
            case BACKWARD:
                m_pos -= m_front * cameraSpeed;
                break;
            case RIGHT:
                m_pos += glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
                break;
            case LEFT:
                m_pos -= glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
                break;
            default:
                break;
        }
    }

    void Camera::processMouse(float xOffset, float yOffset, bool constrainPitch) {
        xOffset *= m_mouseSensibility;
        yOffset *= m_mouseSensibility;
        m_yaw += xOffset;
        m_pitch += yOffset;
        if (constrainPitch) {
            if (m_pitch > 89.0f)
                m_pitch = 89.0f;
            if (m_pitch < -89.0f)
                m_pitch = -89.0f;
        }
        updateFront();
    }

    void Camera::updateFront() {
        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(direction);
    }

    void Camera::processScroll(float yOffset) {
        m_fov -= yOffset;
        if (m_fov < 1.0f)
            m_fov = 1.0f;
        if (m_fov > 45.0f)
            m_fov = 45.0f;
    }
} // namespace GLTool


