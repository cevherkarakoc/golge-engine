#ifndef GOLGE_SPRITE_RENDERER_H
#define GOLGE_SPRITE_RENDERER_H

#include <memory>
#include <glm/glm.hpp>

#include <golge/game/component.h>
#include <golge/core/mesh.h>
#include <golge/core/material.h>

using glm::vec2;
using glm::vec3;

namespace golge
{
class SpriteRenderer : public Component
{
public:
  SpriteRenderer(Material::SharedPtr material, float tileNumber = 0.0);
  void init();
  void update(float deltaTime);
  std::string getName() const;
  void setTileNumber(float tileNumber);
  void setOrder(float order);

  void static staticInit();
  static Mesh::UniquePtr SQUARE_MESH;

private:
  Material::SharedPtr m_material;
  float m_tileNumber;
  float m_order;
};
} // namespace golge

#endif