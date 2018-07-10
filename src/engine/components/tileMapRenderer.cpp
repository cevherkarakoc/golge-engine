#include <golge/engine/components/tileMapRenderer.h>

#include <golge/engine/components/transformComponent.h>
#include <golge/engine/components/spriteRenderer.h>

using namespace golge;

TileMapRenderer::TileMapRenderer(Tilemap::SharedPtr tilemap, std::vector<Material::SharedPtr> materials, bool isometric)
{
  m_name = "tilemap_renderer";

  m_tilemap = tilemap;
  m_materials = materials;
  m_isometric = isometric;
}

void TileMapRenderer::init()
{
  int materialIndex = 0;
  int height = m_tilemap->getHeight();
  int width = m_tilemap->getWidth();
  int layerCount = m_tilemap->getLayerCount();

  float offsetX = 0.0, offsetY = 1.0, centerX = 0.5, centerY = 0.5;

  if(m_isometric)
  {
    offsetX = 0.5;
    offsetY = 0.5;
    centerX = 0.0;
    centerY = 0.25;
  }

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

        auto tile = Entity::create(m_entity->getName() + "tile" + std::to_string(l) + std::to_string(index));

        Component::SharedPtr transform(new TransformComponent());
        Component::SharedPtr renderer(new SpriteRenderer(m_materials[materialIndex], tileNumber));

        float x, y;

        x = (j  * offsetY) +  (-i * offsetX);
        y = (-i * offsetY) -  (x  * offsetX);

        x -= width * centerX;
        y += height * centerY;

        std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setPosition(x, y);
        std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setScale(1.015, 1.015);

        float order = -1000.0;
        if (l > 0)
          order = y;
        std::dynamic_pointer_cast<SpriteRenderer>(renderer)->setOrder(order);

        tile->addComponent(renderer);
        tile->addComponent(transform);

        tile->setParent(m_entity);
        tile->setScene(m_entity->getScene());
        tile->init();

        m_tiles.push_back(tile);
      }
    }
  }

  m_materials.clear();
}

void TileMapRenderer::update(float deltaTime)
{
  for (auto const &tile : m_tiles)
  {
    tile->update(deltaTime);
  }
}