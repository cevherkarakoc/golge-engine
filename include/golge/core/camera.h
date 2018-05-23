#ifndef GOLGE_CAMERA_H
#define GOLGE_CAMERA_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;

namespace golge
{

class Camera
{
public:
  using SharedPtr = std::shared_ptr<Camera>;

  Camera(vec3 position, vec3 up, float fov, float aspect, float zNear, float zFar, float yaw, float pitch);

  inline vec3 getPosition() const { return m_position; };

  void setPosition(vec3 position);
  void setPosition(float x, float y, float z);

  void moveForward(float speed);
  void moveRight(float speed);

  void pitch(float angle);
  void yaw(float angle);

  inline vec3 getFront() const {return m_front; }
  inline mat4 getView() const { return m_view; }
  inline mat4 getProjection() const { return m_projection; }
  inline mat4 getViewProjection() const { return m_view * m_projection; }

private:
  void calculateView();
  void calculateVectors();

  vec3 m_position;
  vec3 m_worldUp;
  vec3 m_front;
  vec3 m_up;
  vec3 m_right;

  float m_yaw;
  float m_pitch;

  mat4 m_view;
  mat4 m_projection;
};

}
#endif
