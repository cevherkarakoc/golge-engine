#include <golge/game/scene.h>

using namespace golge;

Scene::SharedPtr Scene::create()
{
  SharedPtr scene(new Scene());
  return scene;
}

Scene::Scene() {

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
Scene& Scene::operator=(const Scene &other)
{
  delete m_world;
  m_world = other.getWorld();
  return *this;
}

void Scene::init()
{
  b2Vec2 gravity(0.0f, 0.0f);
  m_world = new b2World(gravity);

  for (auto const &name : m_addingOrder)
  {
    find(name)->init();
  }
}

void Scene::update(float deltaTime)
{
  for (auto const &name : m_addingOrder)
  {
    find(name)->update(deltaTime);
  }

  if (m_physic)
    m_world->Step(deltaTime, 8, 3);
}

void Scene::addEntity(Entity::SharedPtr newEntity)
{
  newEntity->setScene(shared_from_this());
  m_addingOrder.push_back(newEntity->getName());
  m_graph.insert(EntityPair(newEntity->getName(), newEntity));
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