#include <golge/core/camera.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace golge;

Camera::Camera(vec3 position, vec3 up, float fov, float aspect, float zNear, float zFar, float yaw, float pitch)
{
  m_position = position;
  m_worldUp = up;
  m_front = vec3(0.0f, 0.0f, -1.0f);
  m_yaw = yaw;
  m_pitch = pitch;

  m_projection = glm::perspective(fov, aspect, zNear, zFar);
  calculateVectors();
}

void Camera::setPosition(glm::vec3 position)
{
  m_position = vec3(position);
}

void Camera::setPosition(float x, float y, float z)
{
  m_position = vec3(x, y, z);
}

void Camera::moveForward(float speed)
{
  m_position += m_front * speed;
  calculateView();
}

void Camera::moveRight(float speed)
{
  m_position += m_right * speed;
  calculateView();
}

void Camera::pitch(float angle)
{
  m_pitch += angle;
  if (m_pitch > 89.0f)
    m_pitch = 89.0f;
  else if (m_pitch < -89.0f)
    m_pitch = -89.0f;
  calculateVectors();
}

void Camera::yaw(float angle)
{
  m_yaw += angle;
  calculateVectors();
}

void Camera::calculateView()
{
  m_view = glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::calculateVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);

  m_right = glm::normalize(glm::cross(m_front, m_worldUp));
  m_up = glm::normalize(glm::cross(m_right, m_front));

  calculateView();
}
