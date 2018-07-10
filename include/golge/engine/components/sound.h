#ifndef GOLGE_SOUND_H
#define GOLGE_SOUND_H

#include <memory>
#include <string>

#include <golge/engine/soundManager.h>
#include <golge/engine/component.h>

namespace golge
{
class Sound : public Component
{
public:
  Sound(const std::string &soundKey, bool loop = false);
  
  void init(){}
  void update(float deltaTime);
  void message(const Message &msg);

private:
  bool m_play = false;
  sf::Sound m_sound;
};
} // namespace golge

#endif