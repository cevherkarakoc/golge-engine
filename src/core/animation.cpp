#include <golge/core/animation.h>

using namespace golge;

Animation::SharedPtr Animation::create(float start, float end)
{
  SharedPtr animation(new Animation(start, end));
  return animation;
}

Animation::Animation(float start, float end)
{
  m_start = start;
  m_end = end;
  m_frame = start;
}

float Animation::frame()
{
  return m_frame;
}

float Animation::next()
{
  m_frame += 1.0;
  if (m_frame > m_end)
    m_frame = m_start;

  return m_frame;
}