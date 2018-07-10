#ifndef GOLGE_COMPONENT_H
#define GOLGE_COMPONENT_H

#include <memory>
#include <string>

#include <golge/engine/entity.h>
#include <golge/core/messages.h>

namespace golge
{
class Entity;

class Component
{
public:
  using SharedPtr = std::shared_ptr<Component>;

  virtual void init() = 0;
  virtual void update(float deltaTime) = 0;
  virtual void message(const Message &message) {}
  virtual std::string getName() const { return m_name; };

  void setEntity(Entity *entity) { m_entity = entity; }

protected:
  std::string m_name = "";
  Entity *m_entity = nullptr;
};
} // namespace golge

#endif