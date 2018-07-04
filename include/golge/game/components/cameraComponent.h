#ifndef GOLGE_CAMERA_COMPONENT_H
#define GOLGE_CAMERA_COMPONENT_H

#include <golge/core/camera.h>
#include <golge/game/component.h>
#include <golge/game/components/transformComponent.h>

namespace golge
{
class CameraComponent : public Component
{
public:
  CameraComponent(Camera::SharedPtr camera);
  void init();
  void update(float deltaTime);
  std::string getName() const;

private:
  Camera::SharedPtr m_camera;
  std::shared_ptr<TransformComponent> m_transform;
};
} // namespace golge

#endif