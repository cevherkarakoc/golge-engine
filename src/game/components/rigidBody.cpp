#include <golge/game/components/rigidBody.h>

#include "Box2D/Box2D.h"
#include <glm/glm.hpp>

#include <golge/game/components/transformComponent.h>

using namespace golge;

RigidBody::RigidBody() {
  
}

void RigidBody::init() {
  auto pos = m_entity->find<TransformComponent>("transform")->getTransform()->getPosition();

  b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);

	m_body = m_entity->getScene()->getWorld()->CreateBody(&bodyDef);

  m_body->SetUserData( &m_entity );

  b2PolygonShape shape;
  shape.SetAsBox(0.05f, 0.05f);
  m_body->CreateFixture(&shape,0.0f);
}

void RigidBody::update(float deltaTime) {
  auto transform = m_entity->find<TransformComponent>("transform")->getTransform();

	transform->setPosition(m_body->GetPosition().x, m_body->GetPosition().y);
  transform->setRotation(glm::degrees( m_body->GetAngle() ));
}

std::string RigidBody::getName() const{
  return "rigid_body";
}