#include <golge/game/components/move.h>

#include <iostream>

#include <golge/game/inputManager.h>
#include <golge/game/components/transformComponent.h>

using namespace golge;

Move::Move(){

}

void Move::init() {

}

void Move::update() {
  auto transform = m_entity->find<TransformComponent>("transform")->getTransform();
  auto position = transform->getPosition();

	if (InputManager::GetKey("UP") == 1.0)
		position = position + glm::vec2(0.0, 0.01);
	if (InputManager::GetKey("DOWN") == 1.0)
		position = position - glm::vec2(0.0, 0.01);
	if (InputManager::GetKey("RIGHT") == 1.0)
		position = position + glm::vec2(0.01, 0.0);
	if (InputManager::GetKey("LEFT") == 1.0)
		position = position - glm::vec2(0.01, 0.0);

  transform->setPosition(position);
}

std::string Move::getName() const
{
  return "move";
}