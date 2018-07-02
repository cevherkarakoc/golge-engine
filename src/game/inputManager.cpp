#include <golge/game/inputManager.h>

using namespace golge;

std::unordered_map<std::string, float> InputManager::m_keymap = {};

void InputManager::clearInputs() {
  for (auto& keyPair : m_keymap) {
    keyPair.second = 0.0;
	}
}

void InputManager::SetKey(std::string key, float value)
{
  m_keymap.insert_or_assign( key, value );
}

float InputManager::GetKey(std::string key)
{
  auto it = m_keymap.find(key);
  if(it != m_keymap.end())
    return it->second;
  else
    return 0.0;
}