#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/random.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <zen/renderer/ZEN_Shader.h>
#include <zen/renderer/ZEN_VertexArray.h>
#include <zen/time/ZEN_DeltaTime.h>
#include <zen/zen_pch.h>
#include <zen/particles/ZEN_ParticleSystem.h>
namespace Zen {

  class BadParticleSystem {
  public:
    explicit BadParticleSystem(size_t maxParticles = 1000);

    void emit(const ParticleProps &props);

    void update(DeltaTime deltaTime);

    void upload();

    void clear();

    const std::shared_ptr<VertexArray> &vao() const { return m_vao; }
    std::shared_ptr<Shader> &shader() { return m_shader; }

    size_t capacity() const { return m_max; }

    void updateEmitter(ParticleEmitter &emitter, DeltaTime deltaTime);
    void updateEmitters(std::vector<ParticleEmitter> &emitters, DeltaTime deltaTime);

    int32_t aliveCount() const { return m_alive; }

    void setViewProjection(const glm::mat4 &vp) { m_viewProjection = vp; }

  private:
    glm::mat4 m_viewProjection = glm::mat4(1.0f);
    size_t m_max{0};
    int32_t m_alive{0};

    Particles m_particles;

    size_t m_poolIndex{0};

    std::vector<QuadVertex> m_cpuQuad;

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;
    std::shared_ptr<Shader> m_shader;
  };
} // namespace Zen
