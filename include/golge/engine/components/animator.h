#ifndef GOLGE_ANIMATOR_H
#define GOLGE_ANIMATOR_H

#include <golge/engine/component.h>
#include <golge/core/animation.h>

namespace golge
{
class Animator : public Component
{
public:
  Animator(float frameRate, const std::string &name, Animation::SharedPtr animation);
  void init();
  void update(float deltaTime);
  void message(const Message &msg);

  void addAnimation(const std::string &name, Animation::SharedPtr animation);

private:
  float m_frame = -1;
  float m_frameRate;
  float m_time;

  std::unordered_map<std::string, Animation::SharedPtr> m_animations;
  Animation::SharedPtr m_activeAnimation = nullptr;

  void changeActiveAnimation(const std::string &name);
};
} // namespace golge

#endif