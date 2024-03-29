#include <golge/core/contactListener.h>

#include <golge/core/messages.h>
#include <golge/engine/entity.h>

using namespace golge;

void ContactListener::BeginContact(b2Contact *contact)
{
  auto entityA = *static_cast<Entity **>(contact->GetFixtureA()->GetBody()->GetUserData());
  auto entityB = *static_cast<Entity **>(contact->GetFixtureB()->GetBody()->GetUserData());

  CollisionMessage message;
  message.collision = contact;
  message.entityA = entityA;
  message.entityB = entityB;

  m_scene->sendMessage(entityA->getName(), message);
  m_scene->sendMessage(entityB->getName(), message);
}

void ContactListener::EndContact(b2Contact *contact)
{
}

void ContactListener::setScene(Scene *scene)
{
  m_scene = scene;
}