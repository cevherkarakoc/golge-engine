#include <golge/engine/components/cameraComponent.h>

using namespace golge;

CameraComponent::CameraComponent(Camera::SharedPtr camera)
{
  m_name = "camera";

  m_camera = camera;
}

void CameraComponent::init()
{
  m_transform = m_entity->find<TransformComponent>("transform");
}

void CameraComponent::update(float deltaTime)
{
  auto model = m_transform->getModelMatrix();
  m_camera->setPosition(model[3].x, model[3].y, model[3].z);
}