#include <golge/game/components/rigidBody.h>

#include "Box2D/Box2D.h"

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
}

void RigidBody::update(float deltaTime) {

}

std::string RigidBody::getName() const{
  return "rigid_body";
}