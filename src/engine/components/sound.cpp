#include <golge/engine/components/sound.h>

using namespace golge;

Sound::Sound(const std::string &soundKey, bool loop)
{
  m_name = "sound:"+soundKey;

  m_sound.setBuffer(*SoundManager::getSoundBuffer(soundKey));
  m_sound.setLoop(loop);
}

void Sound::update(float deltaTime)
{
  if (m_play)
  {
    m_sound.play();
    m_play = false;
  }
}

void Sound::message(const Message &msg)
{
  switch (msg.type)
  {
  case MessageType::Sound:
    if (m_sound.getStatus() != sf::Sound::Playing)
      m_play = true;
    break;
  }
}