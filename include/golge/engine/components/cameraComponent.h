#ifndef GOLGE_CAMERA_COMPONENT_H
#define GOLGE_CAMERA_COMPONENT_H

#include <golge/core/camera.h>
#include <golge/engine/component.h>
#include <golge/engine/components/transformComponent.h>

namespace golge
{
class CameraComponent : public Component
{
public:
  CameraComponent(Camera::SharedPtr camera);
  void init();
  void update(float deltaTime);

private:
  Camera::SharedPtr m_camera;
  std::shared_ptr<TransformComponent> m_transform;
};
} // namespace golge

#endif