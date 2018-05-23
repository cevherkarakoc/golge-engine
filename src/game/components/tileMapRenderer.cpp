#include <golge/game/components/tileMapRenderer.h>

#include <iostream>

#include <golge/game/components/transformComponent.h>
#include <golge/game/components/spriteRenderer.h>


using namespace golge;

TileMapRenderer::TileMapRenderer(Tilemap::SharedPtr tilemap, Material::SharedPtr material) {
  m_tilemap = tilemap;
  m_material = material;
}

void TileMapRenderer::init() {
  int materialIndex = 0;
  int height = m_tilemap->getHeight();
  int width = m_tilemap->getWidth();

  for(int i = 0 ; i < height; i++) {
    for(int j = 0; j < width; j++) {
      int index = i * width + j;
      int tileNumber = m_tilemap->getTileNumber(index, materialIndex);
      if(tileNumber < 0) continue;
      std::cout<< i << " " << j << " -> " << index << " : " << tileNumber << std::endl;
      auto tile = Entity::create("tile"+std::to_string(index));
      
      Component::SharedPtr transform(new TransformComponent());
	    Component::SharedPtr renderer(new SpriteRenderer(m_material, tileNumber));

      float x = (j * 0.5) + (i * 0.5);
      float y = (i * 0.5) - (x * 0.5) ;
      std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setPosition( x , y );

      tile->addComponent(transform);
      tile->addComponent(renderer);
      tile->setParent(m_entity);
      tile->setScene(m_entity->getScene());

      m_tiles.push_back(tile);
    }
  }
}

void TileMapRenderer::update() {
  for (auto const& tile : m_tiles) {
    tile->update();
  }
}

std::string TileMapRenderer::getName() const {
  return "tile_map_renderer";
}