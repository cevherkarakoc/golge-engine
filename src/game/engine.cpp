#include <golge/game/engine.h>

#include <iostream>

#include <golge/game/inputManager.h>
#include <golge/game/components/spriteRenderer.h>

using namespace golge;

int Engine::init()
{
  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(screenWidth, screenHeight, "Golge Test", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  //glfwSetCursorPosCallback(window, mouse_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::cout << "OPENGL VERSION  : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "OPENGL VENDOR   : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OPENGL RENDERER : " << glGetString(GL_RENDERER) << std::endl;

  SpriteRenderer::staticInit();
}

void Engine::update()
{
  glClearColor(0.70f, 0.85f, 0.95f, 1.0f);

  while (!glfwWindowShouldClose(window))
  {
    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;

    if (deltaTime >= frameTime)
    {
      lastFrame = currentFrame;

      InputManager::clearInputs();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      processInput(window);

      activeScene->update(deltaTime);

      glfwSwapBuffers(window);

      glfwPollEvents();
    }
  }
}

void Engine::destroy()
{
  std::cout<<"DESTROY"<<std::endl;
  glfwTerminate();
}

void Engine::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

unsigned int Engine::getScreenWidth() { return screenWidth; }
unsigned int Engine::getScreenHeight() { return screenHeight; }
float Engine::getTargetFps() { return targetFps; }
float Engine::getFrameTime() { return frameTime; }

void Engine::setScreenWidth(unsigned int width)
{
  screenWidth = width;
}
void Engine::setScreenHeight(unsigned int height)
{
  screenHeight = height;
}
void Engine::setTargetFps(float fps)
{
  targetFps = fps;
  frameTime = 1.0 / targetFps;
}

void Engine::setActiveScene(Scene::SharedPtr scene)
{
  activeScene = scene;
}

void Engine::addScene(const std::string &name, Scene::SharedPtr scene)
{
  scenes.insert_or_assign(name, scene);
}

bool Engine::loadScene(const std::string &name)
{
  auto it = scenes.find(name);
  if (it != scenes.end()){
    it->second->init();
    setActiveScene(it->second);
  }

}

void Engine::setInputProcessor(std::function<void(GLFWwindow *)> processor)
{
  processInput = processor;
}

SceneMap Engine::scenes = {};

GLFWwindow *Engine::window = nullptr;
std::function<void(GLFWwindow *)> Engine::processInput = nullptr;
unsigned int Engine::screenWidth = 800;
unsigned int Engine::screenHeight = 600;
float Engine::targetFps = 30.0;
float Engine::frameTime = 1.0 / Engine::getTargetFps();
float Engine::deltaTime = 0.0;
float Engine::lastFrame = 0.0;
Scene::SharedPtr Engine::activeScene = nullptr;