#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <golge/core/camera.h>
#include <golge/core/transform.h>
#include <golge/core/shader.h>
#include <golge/core/texture.h>
#include <golge/core/material.h>
#include <golge/core/tilemap.h>
#include <golge/core/mesh.h>

#include <golge/game/scene.h>
#include <golge/game/entity.h>

#include <golge/game/component.h>
#include <golge/game/components/transformComponent.h>
#include <golge/game/components/spriteRenderer.h>
#include <golge/game/components/tileMapRenderer.h>

using namespace golge;
using glm::mat4;
using glm::vec3;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float TARGET_FPS = 60.0;
const float FRAME_TIME = 1.0 / TARGET_FPS;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;																								// 1 1 0
std::shared_ptr<Camera> camera(new Camera(vec3(0.0, 0.0, 10.0), vec3(1.0, 1.0, 0.0), 45.0f,
																					(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f, -90.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

int main(void)
{
	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	std::cout << "OPENGL VERSION : " << glGetString(GL_VERSION) << std::endl;

	float lastFrame = 0.0f;

	// Textures
	auto texTileset = Texture::create("./res/ground.png", 1.0);
	std::cout << "Tileset : " << texTileset->getWidth() << " x " << texTileset->getHeight() << std::endl;

	//Shaders
	auto basicShader = Shader::create("./res/shaders/basic");

	//Materials
	auto matTileset = Material::create(basicShader, texTileset);

	//Tilemap
	auto testTilemap = Tilemap::create("./res/tilemapTest.json");

	//Create Scene
	auto mainScene = Scene::create();
	mainScene->setActiveCamera(camera);

	//Create Entities
	auto tile = Entity::create("tile");

	//Add entities to the scene
	mainScene->addEntity(tile);

	// Components
	Component::SharedPtr transform(new TransformComponent());
	//Component::SharedPtr renderer(new SpriteRenderer(matTileset, 0.0));
	Component::SharedPtr renderer(new TileMapRenderer(testTilemap, matTileset));

	std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setScale(1.0, 1.0);
	std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setRotation(-45.0);

	//Adding Components
	tile->addComponent(transform);
	tile->addComponent(renderer);

	mainScene->init();

	glClearColor(0.70f, 0.85f, 0.95f, 1.0f);
	float counter = 0.0;
	while (!glfwWindowShouldClose(window))
	{
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;

		if (deltaTime >= FRAME_TIME)
		{
			lastFrame = currentFrame;

			processInput(window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			mainScene->update();

			//std::dynamic_pointer_cast<SpriteRenderer>(renderer)->setTileNumber(((int)counter) % 4);
			//std::dynamic_pointer_cast<TransformComponent>(transform)->getTransform()->setPosition(counter, 0.0);
			counter += 0.01;

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveForward(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveForward(-cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRight(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRight(-cameraSpeed);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera->pitch(yoffset * 0.2f);
	camera->yaw(xoffset * 0.2f);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
