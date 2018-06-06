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

	glm::vec2 movementVertical(0.0, 0.0);
	glm::vec2 movementHorizantal(0.0, 0.0);

	if (InputManager::GetKey("UP") == 1.0)
		movementVertical += glm::vec2(0.0, 0.01);
	if (InputManager::GetKey("DOWN") == 1.0)
		movementVertical += glm::vec2(0.0, -0.01);
	if (InputManager::GetKey("RIGHT") == 1.0)
		movementHorizantal += glm::vec2(0.01, 0.0);
	if (InputManager::GetKey("LEFT") == 1.0)
		movementHorizantal += glm::vec2(-0.01, 0.0);

	position += movementVertical;
	position += movementHorizantal;

	m_entity->getScene()->getActiveCamera()->moveUp(movementVertical.y);
	m_entity->getScene()->getActiveCamera()->moveRight(movementHorizantal.x);


  transform->setPosition(position);
}

std::string Move::getName() const
{
  return "move";
}