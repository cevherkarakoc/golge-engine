#include <golge/engine/components/rigidBody.h>

#include "Box2D/Box2D.h"
#include <glm/glm.hpp>

using namespace golge;

RigidBody::RigidBody(b2BodyType bType, float32 hx, float32 hy, float32 cx, float32 cy, float32 angle)
{
  m_name = "rigid_body";

  m_bodyDef.type = bType;
  m_shape.SetAsBox(hx, hy, b2Vec2(cx, cy), glm::radians(angle));
}

void RigidBody::init()
{
  m_transform = m_entity->find<TransformComponent>("transform")->getTransform();

  m_body = m_entity->getScene()->getWorld()->CreateBody(&m_bodyDef);

  m_body->SetUserData(&m_entity);
  m_body->SetTransform(
      b2Vec2(m_transform->getPosition().x, m_transform->getPosition().y),
      m_transform->getRotation());

  m_body->CreateFixture(&m_shape, 0.0f);
}

void RigidBody::update(float deltaTime)
{
  m_transform->setPosition(m_body->GetPosition().x, m_body->GetPosition().y);
  m_transform->setRotation(glm::degrees(m_body->GetAngle()));
}