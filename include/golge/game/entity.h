#ifndef GOLGE_ENTITY_H
#define GOLGE_ENTITY_H

#include <memory>
#include <string>
#include <unordered_map>

#include <golge/game/scene.h>
#include <golge/game/component.h>
#include <golge/core/messages.h>

namespace golge
{
class Scene;
class Component;

using ComponentSharedPtr = std::shared_ptr<Component>;

using CompMap = std::unordered_map<std::string, ComponentSharedPtr>;
using CompPair = std::pair<std::string, ComponentSharedPtr>;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
  using SharedPtr = std::shared_ptr<Entity>;

  static SharedPtr create(const std::string &name);

  Entity(const std::string &name);

  void init();
  void update(float deltaTime);
  void sendMessage(const std::string &component, const Message &message);
  void sendMessage(const Message &message);
  void addComponent(ComponentSharedPtr newComponent);
  void setScene(Scene *scene);
  void setParent(Entity *parent);

  template <class ComponentClass>
  std::shared_ptr<ComponentClass> find(const std::string &name) const
  {
    auto component = m_componentsMap.find(name)->second;
    return std::dynamic_pointer_cast<ComponentClass>(component);
  }

  inline std::string getName() { return m_name; }
  Scene *getScene() const;
  Entity *getParent() const;

private:
  Scene *m_scene = nullptr;
  Entity *m_parent = nullptr;
  std::string m_name;
  std::vector<ComponentSharedPtr> m_components;
  CompMap m_componentsMap;
};
} // namespace golge

#endif