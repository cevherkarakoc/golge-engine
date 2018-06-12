#include <golge/game/components/tileMapRenderer.h>

#include <iostream>

#include <golge/game/components/transformComponent.h>
#include <golge/game/components/spriteRenderer.h>

using namespace golge;

TileMapRenderer::TileMapRenderer(Tilemap::SharedPtr tilemap, std::vector<Material::SharedPtr> materials)
{
  m_tilemap = tilemap;
  m_materials = materials;
}

void TileMapRenderer::init()
{
  int materialIndex = 0;
  int height = m_tilemap->getHeight();
  int width = m_tilemap->getWidth();
  int layerCount = m_tilemap->getLayerCount();

  for (int l = 0; l < layerCount; l++)
  {
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        int index = i * width + j;
        int tileNumber = m_tilemap->getTileNumber(l, index, materialIndex);
        
        if (tileNumber < 0)
          continue;
        
        auto tile = Entity::create("tile" + std::to_string(index));

        Component::SharedPtr transform(new TransformComponent());
        Component::SharedPtr renderer(new SpriteRenderer(m_materials[materialIndex], tileNumber));

        float x = (j * 0.5) + (-i * 0.5);
        float y = (-i * 0.5) - (x * 0.5);

        y += height * 0.25;
        std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setPosition(x, y);
        std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setScale(1.015, 1.015);

        float order = -1000.0;
        if(l > 0) order = y;
        std::dynamic_pointer_cast<SpriteRenderer>(renderer)->setOrder(order);

        tile->addComponent(transform);
        tile->addComponent(renderer);
        tile->setParent(m_entity);
        tile->setScene(m_entity->getScene());

        m_tiles.push_back(tile);
      }
    }
  }
}

void TileMapRenderer::update(float deltaTime)
{
  for (auto const &tile : m_tiles)
  {
    tile->update(deltaTime);
  }
}

std::string TileMapRenderer::getName() const
{
  return "tile_map_renderer";
}