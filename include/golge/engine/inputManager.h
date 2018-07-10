#ifndef GOLGE_INPUT_MANAGER_H
#define GOLGE_INPUT_MANAGER_H

#include <unordered_map>

namespace golge
{
class InputManager
{
public:
  static void clearInputs();
  static void SetKey(std::string key, float value);
  static float GetKey(std::string key);

private:
  static std::unordered_map<std::string, float> m_keymap;
};
} // namespace golge

#endif