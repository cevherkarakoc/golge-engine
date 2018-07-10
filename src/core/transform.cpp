#include <golge/core/transform.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace golge;

Transform::Transform()
{
  m_position = vec3(0.0, 0.0, 0.0);
  m_rotation = 0.0;
  m_scale = vec2(1.0, 1.0);
}

mat4 Transform::getModelMatrix() const
{
  mat4 model;

  mat4 translateMatrix = glm::translate(model, m_position);
  mat4 scaleMatrix = glm::scale(model, glm::vec3(m_scale, 1.0));

  mat4 rotationMatrix = glm::rotate(model, m_rotation, glm::vec3(0.0, 0.0, 1.0));

  return translateMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(glm::vec3 position)
{
  m_position = vec3(position);
}

void Transform::setScale(glm::vec2 scale)
{
  m_scale = vec2(scale);
}

void Transform::setPosition(float x, float y, float z)
{
  m_position = vec3(x, y, z);
}

void Transform::setRotation(GLfloat angle)
{
  m_rotation = angle;
}

void Transform::setScale(float x, float y)
{
  m_scale = vec2(x, y);
}

Transform::~Transform()
{
}
