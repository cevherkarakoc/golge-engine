#ifndef GOLGE_SOUND_H
#define GOLGE_SOUND_H

#include <memory>
#include <string>

#include <golge/game/soundManager.h>
#include <golge/game/component.h>

namespace golge
{
class Sound : public Component
{
public:
  Sound(const std::string &soundKey);
  ~Sound();
  
  void init();
  void update(float deltaTime);
  void message(const Message &msg);
  std::string getName() const;

private:
  bool m_play = false;
  sf::Sound m_sound;
};
} // namespace golge

#endif