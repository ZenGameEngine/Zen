#include <zen/camera/ZEN_Camera.h>

#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Zen {
  Camera::Camera(CameraType type) : m_cameraType(type) {
    updateDirection();
    updateProjection();
    updateView();
  }

  void Camera::setCameraType(CameraType type) {
    m_cameraType = type;
    updateProjection();
    updateView();
  }

  void Camera::setPerspective(float fov, float aspect, float near, float far) {
    m_cameraType  = CameraType::Perspective;
    m_fov         = fov;
    m_aspectRatio = aspect;
    m_near        = near;
    m_far         = far;
    updateProjection();
  }

  void Camera::setOrthographic(float left, float right, float bottom, float top) {
    m_cameraType  = CameraType::Orthographic;
    m_orthoLeft   = left;
    m_orthoRight  = right;
    m_orthoBottom = bottom;
    m_orthoTop    = top;
    updateProjection();
  }

  void Camera::setAspectRatio(float aspect) {
    m_aspectRatio = aspect;
    if (m_cameraType == CameraType::Perspective) {
      updateProjection();
    }
  }

  void Camera::setClip(float near, float far) {
    m_near = near;
    m_far  = far;
    if (m_cameraType == CameraType::Perspective) {
      updateProjection();
    }
  }

  void Camera::setPosition(const glm::vec3 &position) {
    m_position = position;
    updateView();
  }

  void Camera::setRotation(float yaw, float pitch, float roll) {
    m_yaw   = yaw;
    m_pitch = pitch;
    m_roll  = roll;
    clampPitch();
    updateDirection();
    updateView();
  }

  void Camera::setSpeed(float speed) { m_cameraSpeed = speed; }

  void Camera::setSensitivity(float sensitivity) { m_cameraSensitivity = sensitivity; }

  CameraType Camera::type() const { return m_cameraType; }

  const glm::vec3 &Camera::position() const { return m_position; }

  glm::vec3 Camera::rotation() const { return {m_yaw, m_pitch, m_roll}; }

  float Camera::speed() const { return m_cameraSpeed; }

  float Camera::sensitivity() const { return m_cameraSensitivity; }

  float Camera::aspectRatio() const { return m_aspectRatio; }

  const glm::mat4 &Camera::projectionMatrix() const { return m_projection; }

  const glm::mat4 &Camera::viewMatrix() const { return m_view; }

  glm::mat4 Camera::viewProjectionMatrix() const { return m_projection * m_view; }

  void Camera::updateProjection() {
    if (m_cameraType == CameraType::Perspective) {
      m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    } else {
      m_projection = glm::ortho(m_orthoLeft, m_orthoRight, m_orthoBottom, m_orthoTop, -1.0f, 1.0f);
    }
  }

  void Camera::updateView() {
    if (m_cameraType == CameraType::Orthographic) {

      glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_position);
      glm::mat4 roll      = glm::rotate(glm::mat4(1.0f), glm::radians(m_roll), glm::vec3(0, 0, 1));

      m_view = glm::inverse(translate * roll);

    } else {
      const glm::vec3 target = m_position + m_front;

      m_view = glm::lookAt(m_position, target, m_up);
    }
  }

  void Camera::updateDirection() {
    const float yaw   = glm::radians(m_yaw);
    const float pitch = glm::radians(m_pitch);

    glm::vec3 front;
    front.x = std::cos(yaw) * std::cos(pitch);
    front.y = std::sin(pitch);
    front.z = std::sin(yaw) * std::cos(pitch);
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
  }

  void Camera::clampPitch() {
    m_pitch = std::min(m_pitch, 89.0f);
    m_pitch = std::max(m_pitch, -89.0f);
  }

} // namespace Zen