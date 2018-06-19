#ifndef GOLGE_CONTACT_LISTENER_H
#define GOLGE_CONTACT_LISTENER_H

#include <Box2D/Box2D.h>

#include <golge/game/scene.h>

namespace golge
{

class ContactListener : public b2ContactListener
{
public:
  void BeginContact(b2Contact *contact);
  void EndContact(b2Contact *contact);
  void setScene(Scene::SharedPtr scene);

private:
  Scene::SharedPtr m_scene;
};

} // namespace golge

#endif