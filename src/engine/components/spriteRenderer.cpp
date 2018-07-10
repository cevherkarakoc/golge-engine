#include <golge/engine/components/spriteRenderer.h>

#include <vector>

using namespace golge;

SpriteRenderer::SpriteRenderer(Material::SharedPtr material, float tileNumber)
{
  m_name = "sprite_renderer";

  m_material = material.get();
  m_tileNumber = tileNumber;
}

void SpriteRenderer::update(float deltaTime)
{
  auto m_transform = m_entity->find<TransformComponent>("transform");
  auto model = m_transform->getModelMatrix();
  auto scene = m_entity->getScene();
  auto camera = scene->getActiveCamera();

  m_material->use(camera);
  m_material->model(model);
  m_material->updateTileNumber(m_tileNumber);
  m_material->updateOrder(m_order);

  SQUARE_MESH->draw();
}

void SpriteRenderer::message(const Message &msg)
{
  switch (msg.type)
  {
  case MessageType::Animation:
    const AnimationMessage &animationMsg = static_cast<const AnimationMessage &>(msg);

    setTileNumber(animationMsg.tileNumber);

    break;
  }
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