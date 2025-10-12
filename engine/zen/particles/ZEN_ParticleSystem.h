#pragma once

#include <zen/renderer/ZEN_Shader.h>
#include <zen/renderer/ZEN_VertexArray.h>
#include <zen/time/ZEN_DeltaTime.h>
#include <zen/zen_pch.h>

namespace Zen {
  struct ParticleProps {
    glm::vec2 position{0.0f};
    glm::vec2 velocity{0.0f};
    float lifeTime{1.0f};
    float sizeBegin{8.0f};
    float sizeEnd{0.0f};
    glm::vec4 colorBegin{1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec4 colorEnd{1.0f, 1.0f, 1.0f, 0.0f};
  };

  struct Particle {
    glm::vec2 pos{0.0f};
    glm::vec2 vel{0.0f};
    float lifeRemaining{0.0f};
    float lifeTime{1.0f};
    float sizeBegin{8.0f};
    float sizeEnd{0.0f};
    glm::vec4 colorBegin{1.0f};
    glm::vec4 colorEnd{0.0f, 0.0f, 0.0f, 0.0f};
    bool active{false};
  };

  struct QuadVertex {
    glm::vec2 pos;
    glm::vec4 color;
  };

  class ParticleSystem {
  public:
    explicit ParticleSystem(size_t maxParticles = 1000);

    void emit(const ParticleProps &props);

    void update(DeltaTime deltaTime);

    void upload();
    void clear();

    const std::shared_ptr<VertexArray> &vao() const { return m_vao; }
    std::shared_ptr<Shader> &shader() { return m_shader; }

    size_t capacity() const { return m_max; }

  private:
    size_t m_max{0};
    int32_t m_alive{0};
    std::vector<Particle> m_pool;
    size_t m_poolIndex{0};             // ring index

    std::vector<QuadVertex> m_cpuQuad; // size = m_max * 4

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo; // dynamic, max*4 vertices
    std::shared_ptr<IndexBuffer> m_ibo;  // static, max*6 indices
    std::shared_ptr<Shader> m_shader;
  };
} // namespace Zen