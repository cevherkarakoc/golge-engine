#include <golge/game/components/move.h>

#include <iostream>

#include <golge/game/inputManager.h>
#include <golge/game/components/rigidBody.h>
#include <golge/game/components/transformComponent.h>

using namespace golge;

Move::Move()
{
}

void Move::init()
{
}

void Move::update(float deltaTime)
{
	auto rigidBody = m_entity->find<RigidBody>("rigid_body");

	glm::vec2 movementVertical(0.0, 0.0);
	glm::vec2 movementHorizantal(0.0, 0.0);

	float horizantal = InputManager::GetKey("RIGHT") * deltaTime * m_speed;
	horizantal -= InputManager::GetKey("LEFT") * deltaTime * m_speed;

	float vertical = InputManager::GetKey("UP") * deltaTime * m_speed * 0.5;
	vertical -= InputManager::GetKey("DOWN") * deltaTime * m_speed * 0.5;

	rigidBody->m_body->ApplyForceToCenter(b2Vec2(horizantal, vertical), true);

	m_entity->getScene()->getActiveCamera()->moveUp(vertical * 0.01);
	m_entity->getScene()->getActiveCamera()->moveRight(horizantal * 0.01);
}

void Move::message(const Message &msg)
{
	switch (msg.type)
	{
	case MessageType::Collision:
		const CollisionMessage &collisionMsg = static_cast<const CollisionMessage &>(msg);

		std::cout << collisionMsg.entityA->getName() << " x " << collisionMsg.entityB->getName() << std::endl;

		auto transform = m_entity->find<TransformComponent>("transform");
		auto scale = transform->getTransform()->getScale();
		if (scale.x < 2.0)
			scale *= 2.0;
		else
			scale *= 0.5;
			
		transform->getTransform()->setScale(scale);
		break;
	}
}

std::string Move::getName() const
{
	return "move";
}