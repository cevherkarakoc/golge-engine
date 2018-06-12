#ifndef GOLGE_TRANSFORM_COMPONENT_H
#define GOLGE_TRANSFORM_COMPONENT_H

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <golge/core/transform.h>
#include <golge/game/component.h>

namespace golge
{
class TransformComponent : public Component
{
public:
  TransformComponent();
  void init(){}
  void update(float deltaTime);
  std::string getName() const;
  glm::mat4 getModelMatrix() const;

  inline Transform::SharedPtr getTransform() const { return m_transform; }
private:
  Transform::SharedPtr m_transform;
  glm::mat4 m_modelMatrix;
};
}
#endif