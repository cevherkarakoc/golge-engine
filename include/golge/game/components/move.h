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
  void update();
  std::string getName() const;

private:
};
} // namespace golge

#endif