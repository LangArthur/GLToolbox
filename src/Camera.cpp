#include "Camera.hpp"

namespace GLTools
{
    Camera::Camera(const glm::vec3 &cameraPos, const glm::vec3 cameraFront, const glm::vec3 cameraUp)
        : m_pos(cameraPos), m_front(cameraFront), m_worldUp(cameraUp)
    { }

    void Camera::processInput(Movement mov, float deltaTime) {
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
        // modulo 360 to avoid float precision error with very high yaw and pitch
        m_yaw = std::fmod(m_yaw + xOffset, 360.0f);
        m_pitch = std::fmod(m_pitch + yOffset, 360.0f);
        if (constrainPitch) {
            if (m_pitch > 89.0f)
                m_pitch = 89.0f;
            if (m_pitch < -89.0f)
                m_pitch = -89.0f;
        }
        updateCamVectors();
    }

    void Camera::updateCamVectors() {
        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(direction);
        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }

    void Camera::processScroll(float yOffset) {
        m_fov -= yOffset;
        if (m_fov < 1.0f)
            m_fov = 1.0f;
        if (m_fov > 45.0f)
            m_fov = 45.0f;
    }
} // namespace GLTools


