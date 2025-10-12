#pragma once

#include <zen/zen_pch.h>

namespace Zen {
  enum CameraType : uint8_t {
    Orthographic = 1,
    Perspective  = 2,
  };

  class Camera {
  public:
    Camera(CameraType type = CameraType::Orthographic);
    ~Camera() = default;

    void setCameraType(CameraType type);

    void setPerspective(float fov, float aspect, float near, float far);
    void setOrthographic(float left, float right, float bottom, float top);

    void setAspectRatio(float aspect);
    void setClip(float near, float far);

    void setPosition(const glm::vec3 &position);
    void setRotation(float yaw, float pitch, float roll);

    void setSpeed(float speed);
    void setSensitivity(float sensitivity);

    CameraType type() const;
    const glm::vec3 &position() const;
    glm::vec3 rotation() const;
    float speed() const;
    float sensitivity() const;
    float aspectRatio() const;

    const glm::mat4 &projectionMatrix() const;
    const glm::mat4 &viewMatrix() const;
    glm::mat4 viewProjectionMatrix() const;

  private:
    void updateProjection();
    void updateView();
    void updateDirection();
    void clampPitch();

    CameraType m_cameraType;

    glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_front    = {0.0f, 0.0f, -1.0f};
    glm::vec3 m_up       = {0.0f, 1.0f, 0.0f};
    glm::vec3 m_right    = {1.0f, 0.0f, 0.0f};
    glm::vec3 m_worldUp  = {0.0f, 1.0f, 0.0f};

    // glm::vec3 m_focalPoint = {0.0f, 0.0f, 0.0f}; // maybe when I have orbit or pan

    glm::mat4 m_projection{1.0f};
    glm::mat4 m_view{1.0f};

    float m_yaw   = -90.0f;
    float m_pitch = 0.0f;
    float m_roll  = 0.0f;

    float m_fov         = 45.0f;
    float m_aspectRatio = 16.0f / 9.0f; // 16:9
    float m_near        = 0.1f;
    float m_far         = 1000.0f;

    float m_orthoLeft{-10.0f};
    float m_orthoRight{+10.0f};
    float m_orthoBottom{-10.0f};
    float m_orthoTop{+10.0f};

    float m_cameraSpeed       = 1.5f;
    float m_cameraSensitivity = 0.1f;
  };
} // namespace Zen