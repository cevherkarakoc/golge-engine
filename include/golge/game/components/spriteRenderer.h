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
  void update();
  std::string getName() const;
  void setTileNumber(float tileNumber);

private:
  Material::SharedPtr m_material;
  float m_tileNumber;
};
} // namespace golge

#endif