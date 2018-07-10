#include <golge/engine/components/transformComponent.h>

using namespace golge;

TransformComponent::TransformComponent()
{
  m_name = "transform";

  m_transform = Transform::SharedPtr(new Transform());
}

void TransformComponent::update(float deltaTime)
{
  m_modelMatrix = m_transform->getModelMatrix();
}

glm::mat4 TransformComponent::getModelMatrix() const
{
  auto parent = m_entity->getParent();
  if (!parent)
  {
    return m_modelMatrix;
  }

  return parent->find<TransformComponent>(getName())->getModelMatrix() * m_modelMatrix;
}