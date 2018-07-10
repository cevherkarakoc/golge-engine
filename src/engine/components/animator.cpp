#include <golge/engine/components/animator.h>

using namespace golge;

Animator::Animator(float frameRate, const std::string &name, Animation::SharedPtr animation)
{
  m_name = "animator";

  m_frameRate = frameRate;
  addAnimation(name, animation);
  m_activeAnimation = animation;
}

void Animator::init()
{
}

void Animator::update(float deltaTime)
{
  m_time += deltaTime;

  if (m_time >= m_frameRate)
  {
    float frame = m_activeAnimation->frame();
    if (m_frame != frame)
    {
      m_entity->sendMessage("sprite_renderer", AnimationMessage(frame));
      m_time = 0.0;
    }

    m_activeAnimation->next();
  }
}

void Animator::message(const Message &msg)
{
  switch (msg.type)
  {
  case MessageType::Animation:
    const AnimationMessage &animationMsg = static_cast<const AnimationMessage &>(msg);

    changeActiveAnimation(animationMsg.name);

    break;
  }
}

void Animator::addAnimation(const std::string &name, Animation::SharedPtr animation)
{
  m_animations.insert_or_assign(name, animation);
}

void Animator::changeActiveAnimation(const std::string &name)
{
  auto it = m_animations.find(name);
  if (it != m_animations.end())
    m_activeAnimation = it->second;
}