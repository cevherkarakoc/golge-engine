#ifndef GOLGE_ENGINE_H
#define GOLGE_ENGINE_H

#include <functional>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <golge/game/scene.h>

namespace golge
{
using SceneMap = std::unordered_map<std::string, Scene::SharedPtr>;
using ScenePair = std::pair<std::string, Scene::SharedPtr>;

class Engine
{
public:
  static int init();
  static void update();
  static void destroy();

  static void toggleFullscreen();

  static unsigned int getScreenWidth();
  static unsigned int getScreenHeight();
  static float getTargetFps();
  static float getFrameTime();

  static void setScreenWidth(unsigned int width);
  static void setScreenHeight(unsigned int height);
  static void setTargetFps(float fps);

  static void setActiveScene(Scene::SharedPtr scene);
  static void addScene(const std::string &name, Scene::SharedPtr scene);
  static bool loadScene(const std::string &name);

  static void setInputProcessor(std::function<void(GLFWwindow *)> processor);



private:
  static SceneMap scenes;

  static GLFWmonitor *monitor;
  static GLFWwindow *window;
  static std::function<void(GLFWwindow *)> processInput;

  static unsigned int screenWidth;
  static unsigned int screenHeight;
  static float targetFps;
  static float frameTime;

  static float deltaTime;
  static float lastFrame;

  static Scene::SharedPtr activeScene;

  static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

  static bool fullscren;
  static int lastWidth;
  static int lastHeight;
  static int lastPosX;
  static int lastPosY;
};
} // namespace golge

#endif