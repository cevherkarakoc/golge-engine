#include <golge/game/components/move.h>

#include <iostream>

#include <golge/game/inputManager.h>
#include <golge/game/components/rigidBody.h>
#include <golge/game/components/spriteRenderer.h>

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

	float horizantal = InputManager::GetKey("RIGHT") * m_speed;
	horizantal -= InputManager::GetKey("LEFT") * m_speed;

	float vertical = InputManager::GetKey("UP") * m_speed * 0.5;
	vertical -= InputManager::GetKey("DOWN") * m_speed * 0.5;

	//rigidBody->m_body->ApplyForceToCenter(b2Vec2(horizantal, vertical), true);
	rigidBody->m_body->SetLinearVelocity(b2Vec2(horizantal, vertical));

	const float speed = rigidBody->m_body->GetLinearVelocity().Length();

	AnimationMessage msg;

	if (speed > 0.0)
	{
		msg.name = "run";
	}
	else
	{
		msg.name = "idle";
	}

	m_entity->sendMessage("animator", msg);

	if (InputManager::GetKey("ACTION"))
		m_entity->sendMessage("sound", SoundMessage());
}

void Move::message(const Message &msg)
{
	switch (msg.type)
	{
	case MessageType::Collision:
		const CollisionMessage &collisionMsg = static_cast<const CollisionMessage &>(msg);

		SoundMessage soundMsg;

		if (m_entity == collisionMsg.entityA)
			collisionMsg.entityB->sendMessage("sound", soundMsg);
		else
			collisionMsg.entityA->sendMessage("sound", soundMsg);

		break;
	}
}

std::string Move::getName() const
{
	return "move";
}