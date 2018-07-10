#ifndef GOLGE_SPRITE_RENDERER_H
#define GOLGE_SPRITE_RENDERER_H

#include <memory>
#include <glm/glm.hpp>

#include <golge/engine/component.h>
#include <golge/core/mesh.h>
#include <golge/core/material.h>

#include <golge/engine/components/transformComponent.h>

using glm::vec2;
using glm::vec3;

namespace golge
{
class SpriteRenderer : public Component
{
public:
  SpriteRenderer(Material::SharedPtr material, float tileNumber = 0.0);
  void init() {}
  void update(float deltaTime);
  void message(const Message &msg);

  void setTileNumber(float tileNumber);
  void setOrder(float order);

  void static staticInit();
  static Mesh::UniquePtr SQUARE_MESH;

private:
  Material *m_material;
  std::shared_ptr<TransformComponent> m_transform;
  float m_tileNumber;
  float m_order;
};
} // namespace golge

#endif