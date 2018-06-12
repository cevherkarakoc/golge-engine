#ifndef GOLGE_MOVE_H
#define GOLGE_MOVE_H

#include <golge/game/component.h>

namespace golge
{
class Move : public Component
{
public:
  Move();
  void init();
  void update(float deltaTime);
  std::string getName() const;

private:
  float m_speed = 50.0;
};
} // namespace golge

#endif