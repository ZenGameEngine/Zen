#pragma once

#include <editor/src/QuadBuilder.h>
#include <glm/fwd.hpp>
#include <memory>
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
    std::shared_ptr<Shader> m_shader;
    int m_capacity = 10000;
    std::unique_ptr<ParticleSystem> m_particleSystem;
    QuadBuilder m_quadBuilder;

    float m_emitAccumulator{0.0f};
    float m_spawnRate = 60.0f;
    ParticleEmitter m_particleEmitter;

    const glm::vec2 m_worldMin{-10.0f, -5.625f};
    const glm::vec2 m_worldMax{+10.0f, +5.625f};

    float m_speed                = 3.0f;
    bool m_linkStartSize         = false;
    bool m_linkEndSize           = false;
    bool m_linkEmitterSize       = false;
    bool m_linkEmitterToParticle = false;

    bool m_startup = true;

    int m_spawnRateDummy = 60;
  };
} // namespace Zen