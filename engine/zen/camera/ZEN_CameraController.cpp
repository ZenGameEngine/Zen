#include <zen/camera/ZEN_CameraController.h>

namespace Zen {
  CameraController::CameraController(Camera &camera) : m_camera(camera) {}

  void CameraController::onUpdate(DeltaTime deltaTime) {
    float step = m_camera.speed() * (float)deltaTime;
    if (Input::isKeyHeld(Key::W)) {
      m_cameraPosition.y += step;
    }
    if (Input::isKeyHeld(Key::S)) {
      m_cameraPosition.y -= step;
    }
    if (Input::isKeyHeld(Key::D)) {
      m_cameraPosition.x += step;
    }
    if (Input::isKeyHeld(Key::A)) {
      m_cameraPosition.x -= step;
    }

    m_camera.setPosition(m_cameraPosition);
  }

  bool CameraController::onEvent(const ZenEvent &event) {
    if (event.header.type == EventType::MouseScrolled) {
      return this->onMouseScrolled(event);
    }
    if (event.header.type == EventType::WindowResize) {
      return this->onWindowResize(event);
    }
    return false;
  }

  bool CameraController::onMouseScrolled(const ZenEvent &event) {
    m_aspectRatio = m_camera.aspectRatio();
    m_zoomLevel -= (float)event.mouseWheel.scrl_height * 0.25f;
    m_zoomLevel = std::max(m_zoomLevel, 0.25f);
    m_camera.setOrthographic(-m_aspectRatio * m_zoomLevel,
                             m_aspectRatio * m_zoomLevel,
                             -m_zoomLevel,
                             m_zoomLevel);
    return false;
  }

  bool CameraController::onWindowResize(const ZenEvent &event) {
    m_aspectRatio = (float)event.windowResize.width / (float)event.windowResize.height;
    m_camera.setOrthographic(-m_aspectRatio * m_zoomLevel,
                             m_aspectRatio * m_zoomLevel,
                             -m_zoomLevel,
                             m_zoomLevel);
    return false;
  }
} // namespace Zen