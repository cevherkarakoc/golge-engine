#include <golge/game/components/move.h>

#include <iostream>

#include <golge/game/inputManager.h>
#include <golge/game/components/transformComponent.h>
#include <golge/game/components/rigidBody.h>

using namespace golge;

Move::Move(){

}

void Move::init() {

}

void Move::update(float deltaTime) {
  auto transform = m_entity->find<TransformComponent>("transform")->getTransform();
	auto rigidBody = m_entity->find<RigidBody>("rigid_body");

  auto position = transform->getPosition();

	glm::vec2 movementVertical(0.0, 0.0);
	glm::vec2 movementHorizantal(0.0, 0.0);

	transform->setPosition(rigidBody->m_body->GetPosition().x, rigidBody->m_body->GetPosition().y);

	float horizantal = InputManager::GetKey("RIGHT") * deltaTime * m_speed;
	horizantal -= InputManager::GetKey("LEFT") * deltaTime * m_speed;

	float vertical = InputManager::GetKey("UP") * deltaTime * m_speed * 0.5;
	vertical -= InputManager::GetKey("DOWN") * deltaTime * m_speed * 0.5;

	rigidBody->m_body->SetLinearVelocity(b2Vec2(horizantal, vertical));

	m_entity->getScene()->getActiveCamera()->moveUp(vertical * 0.01);
	m_entity->getScene()->getActiveCamera()->moveRight(horizantal * 0.01);
}

std::string Move::getName() const
{
  return "move";
}