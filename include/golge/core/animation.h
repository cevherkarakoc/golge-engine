#ifndef GOLGE_ANIMATION_H
#define GOLGE_ANIMATION_H

#include <memory>

namespace golge
{
  class Animation
{
public:
  using SharedPtr = std::shared_ptr<Animation>;

  static SharedPtr create(float start, float end);

  Animation(float start, float end);
  float nextFrame();

private:
  float m_start;
  float m_end;
  float m_frameRate;
  float m_frame;
  float m_time;
};
}

#endif