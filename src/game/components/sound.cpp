#include <golge/game/components/sound.h>

#include <iostream>

using namespace golge;

Sound::Sound(const std::string &soundKey)
{
  m_sound.setBuffer(*SoundManager::getSoundBuffer(soundKey));
}

Sound::~Sound()
{
  std::cout << "sound destroy" << std::endl;
}

void Sound::init()
{
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
    if(m_sound.getStatus() != sf::Sound::Playing)
      m_play = true;
    break;
  }
}

std::string Sound::getName() const
{
  return "sound";
}