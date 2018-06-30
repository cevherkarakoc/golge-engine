#ifndef GOLGE_SOUND_MANAGER_H
#define GOLGE_SOUND_MANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Audio.hpp>



namespace golge
{
class SoundManager
{
  using BufferSharedPtr = std::shared_ptr<sf::SoundBuffer>;

public:
  static void loadSound(const std::string &file, const std::string &key);
  static BufferSharedPtr getSoundBuffer(const std::string &key);
private:
  static std::unordered_map<std::string, BufferSharedPtr> m_buffers;
  
};
} // namespace golge

#endif