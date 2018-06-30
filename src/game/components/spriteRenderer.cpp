#include <golge/game/components/spriteRenderer.h>

#include <vector>
#include <iostream>

using namespace golge;

SpriteRenderer::SpriteRenderer(Material::SharedPtr material, float tileNumber)
{
  m_material = material;
  m_tileNumber = tileNumber;
}

void SpriteRenderer::init()
{
  m_transform = m_entity->find<TransformComponent>("transform");
}

void SpriteRenderer::update(float deltaTime)
{
  auto model = m_transform->getModelMatrix();
  auto scene = m_entity->getScene();
  auto camera = scene->getActiveCamera();

  m_material->use(camera); 
  m_material->model(model); 
  m_material->updateTileNumber(m_tileNumber); 
  m_material->updateOrder(m_order);
  
  SQUARE_MESH->draw();
}

std::string SpriteRenderer::getName() const
{
  return "sprite_renderer";
}

void SpriteRenderer::setTileNumber(float tileNumber)
{
  m_tileNumber = tileNumber;
}

void SpriteRenderer::setOrder(float order)
{
  m_order = order;
}

void SpriteRenderer::staticInit()
{
  Vertex vsa[4] = {
      {vec3(-0.5, -0.5, 0), vec2(0, 1)},
      {vec3(0.5, -0.5, 0), vec2(1, 1)},
      {vec3(0.5, 0.5, 0), vec2(1, 0)},
      {vec3(-0.5, 0.5, 0), vec2(0, 0)}};
  std::vector<Vertex> vs(vsa, vsa + 4);

  unsigned int uia[6] = {0, 1, 2, 0, 2, 3};
  std::vector<unsigned int> inds(uia, uia + 6);
  Mesh msh(vs, inds);

  Mesh::UniquePtr sMesh(new Mesh(vs, inds));

  SQUARE_MESH = std::move(sMesh);
}

Mesh::UniquePtr SpriteRenderer::SQUARE_MESH = nullptr;