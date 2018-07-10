#ifndef GOLGE_TRANSFORM_H
#define GOLGE_TRANSFORM_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

using glm::mat4;
using glm::vec2;
using glm::vec3;

namespace golge
{

class Transform
{
public:
  using SharedPtr = std::shared_ptr<Transform>;

  Transform();

  mat4 getModelMatrix() const;

  inline vec3 getPosition() const { return m_position; }
  inline GLfloat getRotation() const { return m_rotation; }
  inline vec2 getScale() const { return m_scale; }

  void setPosition(vec3 position);
  void setScale(vec2 scale);

  void setPosition(float x, float y, float z = 0.0);
  void setRotation(GLfloat angle);
  void setScale(float x, float y);

  ~Transform();

private:
  vec3 m_position;
  GLfloat m_rotation;
  vec2 m_scale;
};
} // namespace golge

#endif
