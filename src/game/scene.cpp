#include <golge/game/scene.h>

#include <iostream>

#include <golge/core/contactListener.h>

using namespace golge;

ContactListener theContactListener;

Scene::SharedPtr Scene::create()
{
  SharedPtr scene(new Scene());
  return scene;
}

Scene::Scene()
{
}

Scene::~Scene()
{
  delete m_world;
}

Scene::Scene(const Scene &other)
{
  b2World *world = other.m_world;
  m_world = world;
}
Scene &Scene::operator=(const Scene &other)
{
  delete m_world;
  m_world = other.getWorld();
  return *this;
}

void Scene::init()
{
  b2Vec2 gravity(0.0f, 0.0f);
  m_world = new b2World(gravity);
  theContactListener.setScene(this);
  m_world->SetContactListener(&theContactListener);

  for (auto const &entity : m_entities)
  {
    entity->init();
  }
}

void Scene::update(float deltaTime)
{
  for (auto const &entity : m_entities)
  {
    entity->update(deltaTime);
  }

  if (m_physic)
    m_world->Step(deltaTime, 8, 3);
}

void Scene::sendMessage(const std::string &entity, const std::string &component, const Message &message)
{
  auto it = m_graph.find(entity);
  if (it != m_graph.end())
    it->second->sendMessage(component, message);
}

void Scene::sendMessage(const std::string &entity, const Message &message)
{
  auto it = m_graph.find(entity);
  if (it != m_graph.end())
    it->second->sendMessage(message);
}

void Scene::addEntity(Entity::SharedPtr newEntity)
{
  newEntity->setScene(this);
  m_graph.insert(EntityPair(newEntity->getName(), newEntity));
  m_entities.push_back(newEntity);
}

void Scene::setActiveCamera(Camera::SharedPtr camera)
{
  m_camera = camera;
}

void Scene::setLights(LightVector lights)
{
  m_lights = lights;
}

void Scene::setPhysic(bool physic)
{
  m_physic = physic;
}

Entity::SharedPtr Scene::find(const std::string &name) const
{
  auto it = m_graph.find(name);
  return it->second;
}

b2World *Scene::getWorld() const
{
  return m_world;
}