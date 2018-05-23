#include <golge/game/components/spriteRenderer.h>

#include <vector>
#include <iostream>

#include <golge/game/components/transformComponent.h>

using namespace golge;

SpriteRenderer::SpriteRenderer(Material::SharedPtr material, float tileNumber)
{
  m_material = material;
  m_tileNumber = tileNumber;
}

void SpriteRenderer::init()
{
}

void SpriteRenderer::update()
{
  auto model = m_entity->find<TransformComponent>("transform")->getModelMatrix();
  auto scene = m_entity->getScene();
  auto camera = scene->getActiveCamera();

  m_material->use(camera);
  m_material->model(model);
  m_material->updateTileNumber(m_tileNumber);

  Vertex vsa[4] = {
      {vec3(-0.5, -0.5, 0), vec2(0, 1)},
      {vec3(0.5, -0.5, 0), vec2(1, 1)},
      {vec3(0.5, 0.5, 0), vec2(1, 0)},
      {vec3(-0.5, 0.5, 0), vec2(0, 0)}};
  std::vector<Vertex> vs(vsa, vsa + 4);

  unsigned int uia[6] = {0, 1, 2, 0, 2, 3};
  std::vector<unsigned int> inds(uia, uia + 6);

  Mesh::UniquePtr sMesh(new Mesh(vs, inds));

  sMesh->draw();
}

std::string SpriteRenderer::getName() const
{
  return "sprite_renderer";
}

void SpriteRenderer::setTileNumber(float tileNumber)
{
  m_tileNumber = tileNumber;
}