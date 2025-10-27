#pragma once

#include <zen/camera/ZEN_Camera.h>
#include <zen/events/ZEN_Event.h>
#include <zen/inputs/ZEN_Input.h>
#include <zen/time/ZEN_DeltaTime.h>
#include <zen/utility/ZEN_Macros.h>
#include <zen/zen_pch.h>

namespace Zen {
  class CameraController {
  public:
    CameraController(Camera &camera);
    void onUpdate(DeltaTime deltaTime);
    bool onEvent(const ZenEvent &event);

    bool onMouseScrolled(const ZenEvent &event);
    bool onWindowResize(const ZenEvent &event);

    void setWorldBounds(float left, float right, float bottom, float top);
    void enableWorldBounds(bool enabled);

  private:
    void updateCameraProjection();
    void clampCameraToWorld();
    void getViewDimensions(float &outWidth, float &outHeight) const;

    Camera &m_camera;
    float m_aspectRatio;
    float m_zoomLevel = 1.0f;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};

    bool m_worldBoundsEnabled = false;
    float m_worldLeft         = -10.0f;
    float m_worldRight        = 10.0f;
    float m_worldBottom       = -5.625f;
    float m_worldTop          = 5.625f;

    float m_worldWidth       = 20.0f;
    float m_worldHeight      = 11.25f;
    float m_worldAspectRatio = 16.0f / 9.0f;
  };
} // namespace Zen
