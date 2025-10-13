
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <include/imgui/imgui.h>
#include <zen/particles/ZEN_ParticleTestLayer.h>
#include <zen/renderer/ZEN_RenderCommand.h>
#include <zen/renderer/ZEN_Renderer.h>

namespace Zen {
  void ParticleTestLayer::onAttach() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_camera.setPosition({0.0f, 0.0f, 0.0f});
    m_camera.setOrthographic(-10.0f, 10.0f, -5.625f, 5.625f);

    m_ps                   = std::make_unique<ParticleSystem>(2000);
    m_particle.position    = {0.0f, 0.0f};
    m_particle.velocity    = {(float)(((rand() % 400) / 100.0) - 2.0),
                              (float)(((rand() % 300) / 100.0) + 2.0)};
    m_particle.lifeTime    = 3.0f;
    m_particle.sizeBegin   = 1.0f;
    m_particle.sizeEnd     = 0.0f;
    m_particle.colourBegin = {1.0f, 0.7f, 0.3f, 1.0f};
    m_particle.colourEnd   = {1.0f, 0.2f, 0.0f, 1.0f};
  }

  void ParticleTestLayer::onUpdate(DeltaTime deltaTime) {
    m_cameraController.onUpdate(deltaTime);
    RenderCommand::setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::clear();

    float rate   = m_spawnRate;
    float period = 1.0f / glm::max(rate, 0.001f);

    m_emitAccumulator += deltaTime.seconds();
    while (m_emitAccumulator > period) {
      m_particle.velocity = {(float)(((rand() % 400) / 100.0) - 2.0),
                             (float)(((rand() % 300) / 100.0) + 2.0)};
      m_ps->emit(m_particle);
      m_emitAccumulator -= period;
    }

    m_ps->update(deltaTime);
    m_ps->upload();

    Renderer::beginScene(m_camera);
    Renderer::submit(m_ps->shader(), m_ps->vao());
    Renderer::endScene();
  }

  bool ParticleTestLayer::onEvent(const ZenEvent &event) {
    // m_cameraController.onEvent(event);
    return false;
  }

  void ParticleTestLayer::onGUIRender() {
    ImGui::Begin("Particle Settings");
    ImGui::ColorEdit4("Birth Color", glm::value_ptr(m_particle.colourBegin));
    ImGui::ColorEdit4("Death Color", glm::value_ptr(m_particle.colourEnd));
    if (ImGui::DragFloat("Lifetime", &m_particle.lifeTime, 0.1f, 0.01f, 1000.0f)) {
      m_ps->clear();
    }
    ImGui::DragFloat("Size (beginning)", &m_particle.sizeBegin, 0.1f, 0.1f, 100.0f);
    ImGui::DragFloat("Size (end)", &m_particle.sizeEnd, 0.1f, 0.0f, 100.0f);
    ImGui::DragFloat("Spawn Rate (p/s)", &m_spawnRate, 1.0f, 1.0f, 1000.0f);
    ImGui::End();
  }
} // namespace Zen