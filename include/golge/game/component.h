#ifndef GOLGE_COMPONENT_H
#define GOLGE_COMPONENT_H

#include <memory>
#include <string>

#include <golge/game/entity.h>

namespace golge
{
class Entity;
using EntitySharedPtr = std::shared_ptr<Entity>;

class Component
{
public:
  using SharedPtr = std::shared_ptr<Component>;

  virtual void init() = 0;
  virtual void update(float deltaTime) = 0;
  virtual std::string getName() const = 0;

  inline void setEntity(EntitySharedPtr entity) { m_entity = entity; }
protected:
  EntitySharedPtr m_entity;
};
}

#endif