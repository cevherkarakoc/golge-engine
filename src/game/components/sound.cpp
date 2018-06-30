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
}

void Sound::message(const Message &msg)
{
  switch (msg.type)
  {
  case MessageType::Sound:
    m_sound.play();
    break;
  }
}

std::string Sound::getName() const
{
  return "sound";
}