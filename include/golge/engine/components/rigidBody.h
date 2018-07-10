#ifndef GOLGE_RIGID_BODY_RENDERER_H
#define GOLGE_RIGID_BODY_RENDERER_H

#include <memory>
#include <glm/glm.hpp>

#include <golge/engine/component.h>
#include <golge/engine/components/transformComponent.h>

namespace golge
{
class RigidBody : public Component
{
public:
  RigidBody(b2BodyType bType, float32 hx = 1.0f, float32 hy = 1.0f, float32 cx = 0.0f, float32 cy = 0.0f, float32 angle = 0.0f);
  void init();
  void update(float deltaTime);

  b2Body *m_body;

private:
  b2BodyDef m_bodyDef;
  b2PolygonShape m_shape;
  Transform::SharedPtr m_transform;
};
} // namespace golge

#endif