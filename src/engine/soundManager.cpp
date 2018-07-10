#include <golge/engine/soundManager.h>

#include <iostream>

using namespace golge;

void SoundManager::loadSound(const std::string &file, const std::string &key)
{
  BufferSharedPtr buffer(new sf::SoundBuffer());
  if (!buffer->loadFromFile(file))
  {
    std::cout << "Sound File Loading Error : " << file << std::endl;
    return;
  }

  m_buffers.insert_or_assign(key, buffer);
}

SoundManager::BufferSharedPtr SoundManager::getSoundBuffer(const std::string &key)
{
  auto it = m_buffers.find(key);
  if (it != m_buffers.end())
    return it->second;
  else
    return nullptr;
}

std::unordered_map<std::string, SoundManager::BufferSharedPtr> SoundManager::m_buffers = {};