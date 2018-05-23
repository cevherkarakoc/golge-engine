#include <golge/game/scene.h>

using namespace golge;


Scene::SharedPtr Scene::create() {
  SharedPtr scene( new Scene() );
  return scene;
}

void Scene::init() {
  for (auto const& pair : m_graph) {
    pair.second->init();
	}
}

void Scene::update() {
  for (auto const& pair : m_graph) {
    pair.second->update();
	}
}

void Scene::addEntity(Entity::SharedPtr newEntity) {
  newEntity->setScene(shared_from_this());
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