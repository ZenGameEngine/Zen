#include "zen/log/ZEN_Log.h"
#include <zen/camera/ZEN_CameraController.h>

namespace Zen {
  CameraController::CameraController(Camera &camera) : m_camera(camera) {
    m_aspectRatio = m_camera.aspectRatio();
  }

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
    if (m_worldBoundsEnabled) {
      clampCameraToWorld();
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
    if (!m_worldBoundsEnabled) {
      m_aspectRatio = m_camera.aspectRatio();
      m_zoomLevel -= (float)event.mouseWheel.scrl_height * 0.25f;
      m_zoomLevel = std::max(m_zoomLevel, 0.25f);
      m_camera.setOrthographic(-m_aspectRatio * m_zoomLevel,
                               m_aspectRatio * m_zoomLevel,
                               -m_zoomLevel,
                               m_zoomLevel);
    } else {
      m_zoomLevel -= (float)event.mouseWheel.scrl_height * 0.25f;
      m_zoomLevel = std::max(m_zoomLevel, 0.25f);
      updateCameraProjection();
      clampCameraToWorld();
      m_camera.setPosition(m_cameraPosition);
    }

    return false;
  }

  bool CameraController::onWindowResize(const ZenEvent &event) {
    m_aspectRatio = (float)event.windowResize.width / (float)event.windowResize.height;

    if (!m_worldBoundsEnabled) {
      m_camera.setOrthographic(-m_aspectRatio * m_zoomLevel,
                               m_aspectRatio * m_zoomLevel,
                               -m_zoomLevel,
                               m_zoomLevel);
    } else {
      updateCameraProjection();
      clampCameraToWorld();
      m_camera.setPosition(m_cameraPosition);
    }

    ZEN_LOG_DEBUG("aspect ratio: {}", m_aspectRatio);
    return false;
  }

  void CameraController::setWorldBounds(float left, float right, float bottom, float top) {
    m_worldLeft   = left;
    m_worldRight  = right;
    m_worldBottom = bottom;
    m_worldTop    = top;

    m_worldWidth       = m_worldRight - m_worldLeft;
    m_worldHeight      = m_worldTop - m_worldBottom;
    m_worldAspectRatio = m_worldWidth / m_worldHeight;

    if (m_worldBoundsEnabled) {
      updateCameraProjection();
      clampCameraToWorld();
      m_camera.setPosition(m_cameraPosition);
    }
  }

  void CameraController::enableWorldBounds(bool enabled) {
    m_worldBoundsEnabled = enabled;
    if (enabled) {
      updateCameraProjection();
      clampCameraToWorld();
      m_camera.setPosition(m_cameraPosition);
    }
  }

  void CameraController::getViewDimensions(float &outWidth, float &outHeight) const {
    // the world has a fixed size: m_worldWidth x m_worldHeight
    // use this to adjust the view to match the world while respecting zoom and aspect ratio

    float baseWidth  = m_worldWidth / m_zoomLevel;
    float baseHeight = m_worldHeight / m_zoomLevel;

    float zoomedWorldAspect = baseWidth / baseHeight;

    if (m_aspectRatio > zoomedWorldAspect) {
      // window is WIDER than the zoomed world
      // lock width to world, crop height
      outWidth  = baseWidth;
      outHeight = baseWidth / m_aspectRatio;
    } else {
      // window is TALLER/EQUAL to the zoomed world
      // lock height to world, crop width
      outHeight = baseHeight;
      outWidth  = baseHeight * m_aspectRatio;
    }
  }

  void CameraController::updateCameraProjection() {
    float viewWidth;
    float viewHeight;
    getViewDimensions(viewWidth, viewHeight);

    float halfWidth  = viewWidth / 2.0f;
    float halfHeight = viewHeight / 2.0f;

    m_camera.setOrthographic(-halfWidth, halfWidth, -halfHeight, halfHeight);

    ZEN_LOG_DEBUG("View size: {}x{}, Zoom: {}, Aspect: {}",
                  viewWidth,
                  viewHeight,
                  m_zoomLevel,
                  m_aspectRatio);
  }

  void CameraController::clampCameraToWorld() {
    const float minZoomOut = 1.0f;
    float oldZoom          = m_zoomLevel;
    m_zoomLevel            = std::max(m_zoomLevel, minZoomOut);
    if (m_zoomLevel != oldZoom) {
      updateCameraProjection();
    }
    float viewWidth;
    float viewHeight;
    getViewDimensions(viewWidth, viewHeight);

    float halfWidth  = viewWidth / 2.0f;
    float halfHeight = viewHeight / 2.0f;

    // calculate world center
    float worldCenterX = (m_worldLeft + m_worldRight) / 2.0f;
    float worldCenterY = (m_worldBottom + m_worldTop) / 2.0f;

    // clamp camera position so view edges don't exceed world bounds
    // x axis clamping
    if (viewWidth >= m_worldWidth) {
      // view is wider than world, center camera on world x
      m_cameraPosition.x = worldCenterX;
    } else {
      // view is smaller, clamp position so edges stay within world
      float minX         = m_worldLeft + halfWidth;
      float maxX         = m_worldRight - halfWidth;
      m_cameraPosition.x = std::clamp(m_cameraPosition.x, minX, maxX);
    }

    // x axis clamping
    if (viewHeight >= m_worldHeight) {
      // view is taller than world, center camera on world y
      m_cameraPosition.y = worldCenterY;
    } else {
      // view is smaller, clamp position so edges stay within world
      float minY         = m_worldBottom + halfHeight;
      float maxY         = m_worldTop - halfHeight;
      m_cameraPosition.y = std::clamp(m_cameraPosition.y, minY, maxY);
    }

    ZEN_LOG_DEBUG("Camera pos: ({}, {}), View: {}x{}",
                  m_cameraPosition.x,
                  m_cameraPosition.y,
                  viewWidth,
                  viewHeight);
  }

} // namespace Zen