#ifndef GOLGE_SCENE_H
#define GOLGE_SCENE_H

#include <memory>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>

#include "Box2D/Box2D.h"

#include <golge/game/entity.h>
#include <golge/core/material.h>
#include <golge/core/camera.h>
#include <golge/core/messages.h>

namespace golge
{
class Entity;

using EntitySharedPtr = std::shared_ptr<Entity>;
using EntityMap = std::unordered_map<std::string, EntitySharedPtr>;
using EntityPair = std::pair<std::string, EntitySharedPtr>;
using LightVector = std::vector<Light::SharedPtr>;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
  using SharedPtr = std::shared_ptr<Scene>;

  static SharedPtr create();

  Scene();
  virtual ~Scene();
  Scene(const Scene &other);
  Scene &operator=(const Scene &other);

  void init();
  void update(float deltaTime);
  void sendMessage(const std::string &entity, const std::string &component, const Message &message);
  void sendMessage(const std::string &entity, const Message &message);
  void addEntity(EntitySharedPtr newEntity);
  void setActiveCamera(Camera::SharedPtr camera);
  void setLights(LightVector lights);
  void setPhysic(bool physic);
  EntitySharedPtr find(const std::string &name) const;

  inline Camera::SharedPtr getActiveCamera() const { return m_camera; }
  inline LightVector getLights() const { return m_lights; }
  inline b2World *getWorld() const { return m_world; }

private:
  Camera::SharedPtr m_camera;
  LightVector m_lights;
  std::list<std::string> m_addingOrder;
  EntityMap m_graph;
  std::vector<EntitySharedPtr> m_entities;

  bool m_physic = false;
  b2World *m_world;
};
} // namespace golge

#endif