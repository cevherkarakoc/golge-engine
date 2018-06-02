#ifndef GOLGE_TILE_MAP_RENDERER_H
#define GOLGE_TILE_MAP_RENDERER_H

#include <memory>
#include <list>
#include <vector>
#include <glm/glm.hpp>

#include <golge/game/entity.h>
#include <golge/game/component.h>
#include <golge/core/material.h>
#include <golge/core/tilemap.h>

namespace golge
{
class TileMapRenderer : public Component
{
public:
  TileMapRenderer(Tilemap::SharedPtr tilemap, std::vector<Material::SharedPtr> materials);
  void init();
  void update();
  std::string getName() const;
private:
  Tilemap::SharedPtr m_tilemap;
  std::vector<Material::SharedPtr> m_materials;
  std::list<Entity::SharedPtr> m_tiles;
};
} // namespace golge

#endif
