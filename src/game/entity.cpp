#include <golge/game/entity.h>

#include <golge/game/components/transformComponent.h>

using namespace golge;

Entity::SharedPtr Entity::create(const std::string &name)
{
  SharedPtr entity(new Entity(name));
  return entity;
}

Entity::Entity(const std::string &name)
{
  m_name = name;
}

void Entity::init()
{
  for (auto const &pair : m_components)
  {
    pair.second->init();
  }
}

void Entity::update(float deltaTime)
{
  for (auto const &pair : m_components)
  {
    pair.second->update(deltaTime);
  }
}

void Entity::addComponent(Component::SharedPtr newComponent)
{
  newComponent->setEntity(shared_from_this());
  m_components.insert(CompPair(newComponent->getName(), newComponent));
}

void Entity::setScene(Scene::SharedPtr scene)
{
  m_scene = scene;
}

void Entity::setParent(SharedPtr parent)
{
  m_parent = parent;
}