#pragma once

#include <zen/camera/ZEN_Camera.h>
#include <zen/time/ZEN_DeltaTime.h>
#include <zen/events/ZEN_Event.h>
#include <zen/inputs/ZEN_Input.h>
#include <zen/zen_pch.h>

namespace Zen {
  class CameraController {
  public:
    CameraController(Camera &camera);
    void onUpdate(DeltaTime deltaTime);
    bool onEvent(const ZenEvent &event);

    bool onMouseScrolled(const ZenEvent &event);
    bool onWindowResize(const ZenEvent &event);

  private:
    Camera &m_camera;
    float m_aspectRatio;
    float m_zoomLevel = 1.0f;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};
  };
} // namespace Zen