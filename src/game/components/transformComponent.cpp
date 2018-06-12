#include <golge/game/components/transformComponent.h>

#include <iostream>

using namespace golge;

TransformComponent::TransformComponent()
{
  m_transform = Transform::SharedPtr(new Transform());
}

void TransformComponent::update(float deltaTime)
{
  m_modelMatrix = m_transform->getModelMatrix();
}

std::string TransformComponent::getName() const
{
  return "transform";
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