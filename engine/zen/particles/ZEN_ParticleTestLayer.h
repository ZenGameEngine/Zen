#pragma once

#include <zen/camera/ZEN_Camera.h>
#include <zen/camera/ZEN_CameraController.h>
#include <zen/events/ZEN_Event.h>
#include <zen/layer/ZEN_Layer.h>
#include <zen/particles/ZEN_ParticleSystem.h>
#include <zen/zen_pch.h>

namespace Zen {
  class ParticleTestLayer : public Layer {
  public:
    ParticleTestLayer()
        : Layer(50), m_camera(CameraType::Orthographic), m_cameraController(m_camera) {}

    void onAttach() override;
    void onUpdate(DeltaTime deltaTime) override;
    bool onEvent(const ZenEvent &event) override;
    void onGUIRender() override;

  private:
    Camera m_camera;
    CameraController m_cameraController;
    std::unique_ptr<ParticleSystem> m_ps;
    float m_emitAccumulator{0.0f};
    float m_spawnRate = 60.0f;
    ParticleProps m_particle;
  };
} // namespace Zen