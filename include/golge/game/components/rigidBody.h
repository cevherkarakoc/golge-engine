#ifndef GOLGE_RIGID_BODY_RENDERER_H
#define GOLGE_RIGID_BODY_RENDERER_H

#include <memory>
#include <glm/glm.hpp>

#include <golge/game/component.h>

namespace golge
{
class RigidBody : public Component
{
public:
  RigidBody();
  void init();
  void update(float deltaTime);
  std::string getName() const;

  b2Body *m_body;

private:
  
};
} // namespace golge

#endif