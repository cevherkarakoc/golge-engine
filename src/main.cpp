#include <Box2D/Box2D.h>
#include <memory>
#include <iostream>
#include <vector>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <golge/game/engine.h>
#include <golge/core/camera.h>
#include <golge/core/transform.h>
#include <golge/core/shader.h>
#include <golge/core/texture.h>
#include <golge/core/material.h>
#include <golge/core/tilemap.h>
#include <golge/core/mesh.h>
#include <golge/core/animation.h>

#include <golge/game/scene.h>
#include <golge/game/entity.h>
#include <golge/game/inputManager.h>
#include <golge/game/soundManager.h>

#include <golge/game/component.h>
#include <golge/game/components/animator.h>
#include <golge/game/components/transformComponent.h>
#include <golge/game/components/spriteRenderer.h>
#include <golge/game/components/tileMapRenderer.h>
#include <golge/game/components/rigidBody.h>
#include <golge/game/components/sound.h>

#include <golge/game/components/move.h>

using namespace golge;
using glm::mat4;
using glm::vec3;

//void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);

int init();

/**
	* TODO: ADD Mouse Event Handler
	* TODO: ADD Material  Color
	* TODO: Single Ray to find entity on screen 
*/

auto mainScene = Scene::create();

int main(void)
{
	if (init() == -1)
	{
		return -1;
	}

	std::shared_ptr<Camera> camera(new Camera(vec3(0.0, 0.0, 8.0),
																						vec3(0.0, 1.0, 0.0), 45.0f,
																						(float)Engine::getScreenWidth() / (float)Engine::getScreenHeight(),
																						0.1f, 100.0f, -90.0f, 0.0f));

	// Sounds
	SoundManager::loadSound("./res/Sound/pat.ogg", "pat");
	SoundManager::loadSound("./res/Sound/gun.ogg", "gun");

	// Textures
	auto texHero = Texture::create("./res/hero.png", 2.0);
	auto texZombie = Texture::create("./res/zombie.png", 4.0);
	auto texTileset = Texture::create("./res/testset.png", 2.0);
	auto texTilesetBlue = Texture::create("./res/testsetBlue.png", 2.0);
	std::cout << "hero tex : " << texHero->getWidth() << " x " << texHero->getHeight() << std::endl;

	//Shaders
	auto upShader = Shader::create("./res/shaders/up");
	auto basicShader = Shader::create("./res/shaders/basic");

	//Materials
	auto matHero = Material::create(upShader, texHero);
	auto matZombie = Material::create(upShader, texZombie);
	auto matTileset = Material::create(basicShader, texTileset);
	auto matTilesetBlue = Material::create(basicShader, texTilesetBlue);

	std::vector<Material::SharedPtr> tileMats{matTileset, matTilesetBlue};

	//Tilemap
	auto testTilemap = Tilemap::create("./res/testmap.json");

	//Create Scene

	//auto mainScene = Scene::create();
	mainScene->setActiveCamera(camera);

	//Create Entities
	auto hero = Entity::create("hero");
	auto tile = Entity::create("tile");
	auto stz = Entity::create("stz");

	//Add entities to the scene

	mainScene->addEntity(tile);
	mainScene->addEntity(hero);
	mainScene->addEntity(stz);

	// Components
	Component::SharedPtr transformC(new TransformComponent());
	Component::SharedPtr rendererC(new SpriteRenderer(matHero, 0.0));
	Component::SharedPtr animationC(new Animator(0.1, "idle", Animation::create(0.0, 0.0)));
	Component::SharedPtr rigidC(new RigidBody(b2_dynamicBody, 0.2f, 0.2f));
	Component::SharedPtr move(new Move());
	Component::SharedPtr soundC(new Sound("gun"));

	Component::SharedPtr transformS(new TransformComponent());
	Component::SharedPtr rendererS(new SpriteRenderer(matZombie, 0.0));
	Component::SharedPtr rigidS(new RigidBody(b2_staticBody, 0.05f, 0.05f, 0.0, -0.2));
	Component::SharedPtr soundS(new Sound("pat"));

	Component::SharedPtr transform(new TransformComponent());
	Component::SharedPtr renderer(new TileMapRenderer(testTilemap, tileMats));

	std::dynamic_pointer_cast<Animator>(animationC)->addAnimation("run", Animation::create(2.0, 3.0));

	std::dynamic_pointer_cast<TransformComponent>(transformC)->getTransform()->setScale(0.4, 0.4);
	std::dynamic_pointer_cast<TransformComponent>(transformS)->getTransform()->setPosition(1.0, 1.0);
	//std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setRotation(-45.0);

	//Adding Components
	hero->addComponent(transformC);
	hero->addComponent(rendererC);
	hero->addComponent(animationC);
	hero->addComponent(move);
	hero->addComponent(rigidC);
	hero->addComponent(soundC);

	stz->addComponent(transformS);
	stz->addComponent(rendererS);
	stz->addComponent(rigidS);
	stz->addComponent(soundS);

	tile->addComponent(transform);
	tile->addComponent(renderer);

	mainScene->setPhysic(true);

	Engine::addScene("main", mainScene);
	Engine::loadScene("main");

	Engine::update();

	Engine::destroy();

	return 0;
}

int init()
{
	Engine::setScreenWidth(800);
	Engine::setScreenHeight(600);
	Engine::setTargetFps(60.0);
	Engine::setInputProcessor(processInput);

	return Engine::init();
}

void processInput(GLFWwindow *window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		Engine::toggleFullscreen();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		InputManager::SetKey("UP", 1.0);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		InputManager::SetKey("DOWN", 1.0);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		InputManager::SetKey("RIGHT", 1.0);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		InputManager::SetKey("LEFT", 1.0);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		InputManager::SetKey("ACTION", 1.0);

	auto camera = mainScene->getActiveCamera();
	float cameraSpeed = 2.5f * 1.0 / 60.0;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		camera->moveForward(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		camera->moveForward(-cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera->moveRight(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera->moveRight(-cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->moveUp(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->moveUp(-cameraSpeed);
}

/*
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
		
	}
std::cout<<lastX<<std::endl;
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera->pitch(yoffset * 0.2f);
	camera->yaw(xoffset * 0.2f);
}
*/
