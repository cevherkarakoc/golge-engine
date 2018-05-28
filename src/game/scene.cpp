#include <golge/game/scene.h>

using namespace golge;


Scene::SharedPtr Scene::create() {
  SharedPtr scene( new Scene() );
  return scene;
}

void Scene::init() {
  for (auto const& name : m_addingOrder) {
    find(name)->init();
	}
}

void Scene::update() {
  for (auto const& name : m_addingOrder) {
    find(name)->update();
	}
}

void Scene::addEntity(Entity::SharedPtr newEntity) {
  newEntity->setScene(shared_from_this());
  m_addingOrder.push_back( newEntity->getName() );
  m_graph.insert(EntityPair( newEntity->getName() , newEntity ));
}

void Scene::setActiveCamera(Camera::SharedPtr camera) {
  m_camera = camera;
}

void Scene::setLights(LightVector lights) {
  m_lights = lights;
}

Entity::SharedPtr Scene::find(const std::string &name) const {
  auto it = m_graph.find(name);
  return it->second;
}