#ifndef GOLGE_SCENE_H
#define GOLGE_SCENE_H

#include <memory>
#include <string>
#include <map>
#include <vector>

#include <golge/game/entity.h>
#include <golge/core/material.h>
#include <golge/core/camera.h>

namespace golge
{
class Entity;

using EntitySharedPtr = std::shared_ptr<Entity>;
using EntityMap = std::map<std::string, EntitySharedPtr>;
using EntityPair = std::pair<std::string, EntitySharedPtr>;
using LightVector = std::vector<Light::SharedPtr>;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
  using SharedPtr = std::shared_ptr<Scene>;

  static SharedPtr create();

  void init();
  void update();
  void addEntity(EntitySharedPtr newEntity);
  void setActiveCamera(Camera::SharedPtr camera);
  void setLights(LightVector lights);
  EntitySharedPtr find(const std::string &name) const;

  inline Camera::SharedPtr getActiveCamera() const { return m_camera; }
  inline LightVector getLights() const { return m_lights; }

private:
  Camera::SharedPtr m_camera;
  LightVector m_lights;
  EntityMap m_graph;
};
} // namespace golge

#endif