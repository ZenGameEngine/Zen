#include <glm/fwd.hpp>
#include <glm/gtc/random.hpp>
#include <zen/gui/ZEN_Style.h>
#include <zen/particles/BADParticleSystem.h>
#include <zen/renderer/ZEN_Renderer.h>

namespace Zen {
  BadParticleSystem::BadParticleSystem(size_t maxParticles) : m_max(maxParticles) {

    m_particles.active.reserve(m_max);
    m_particles.positions.reserve(m_max);
    m_particles.velocities.reserve(m_max);
    m_particles.lifeTime.reserve(m_max);
    m_particles.lifeRemaining.reserve(m_max);
    m_particles.sizeBegin.reserve(m_max);
    m_particles.sizeEnd.reserve(m_max);
    m_particles.colourBegin.reserve(m_max);
    m_particles.colourEnd.reserve(m_max);

    m_vao.reset(VertexArray::Create());

    m_vbo.reset(VertexBuffer::Create(nullptr, 4 * sizeof(QuadVertex)));
    m_vbo->setLayout({
        {ShaderDataType::Float2, "a_Position"},
        {ShaderDataType::Float4, "a_Color"   },
    });
    m_vao->addVertexBuffer(m_vbo);

    uint32_t oneQuadIndices[6] = {0, 1, 2, 2, 3, 0};
    m_ibo.reset(IndexBuffer::Create(oneQuadIndices, 6));
    m_vao->setIndexBuffer(m_ibo);

    m_shader = std::make_shared<Shader>("data/particle.vert", "data/particle.frag");

    m_cpuQuad.resize(4);
  }

  void BadParticleSystem::emit(const ParticleProps &p) {
    m_particles.active.push_back(true);
    m_particles.positions.push_back(p.position);
    m_particles.velocities.push_back(p.velocity);
    m_particles.lifeTime.push_back(p.lifeTime);
    m_particles.lifeRemaining.push_back(p.lifeTime);
    m_particles.sizeBegin.push_back(p.sizeBegin);
    m_particles.sizeEnd.push_back(p.sizeEnd);
    m_particles.colourBegin.push_back(p.colourBegin);
    m_particles.colourEnd.push_back(p.colourEnd);
  }

  void BadParticleSystem::update(DeltaTime deltaTime) {
    float dt = deltaTime.seconds();
    m_alive  = 0;

    for (size_t i = 0; i < m_particles.active.size(); ++i) {
      if (!m_particles.active[i])
        continue;

      m_particles.lifeRemaining[i] -= dt;
      if (m_particles.lifeRemaining[i] <= 0.f) {
        m_particles.active[i] = false;
        continue;
      }

      m_particles.positions[i] += m_particles.velocities[i] * dt;

      float t        = 1.0f - (m_particles.lifeRemaining[i] / m_particles.lifeTime[i]);
      glm::vec2 size = glm::mix(m_particles.sizeBegin[i], m_particles.sizeEnd[i], t);
      glm::vec4 col  = glm::mix(m_particles.colourBegin[i], m_particles.colourEnd[i], t);

      glm::vec2 h   = size * 0.5f;
      QuadVertex *v = &m_cpuQuad[0];
      v[0]          = {m_particles.positions[i] + glm::vec2(-h.x, -h.y), col};
      v[1]          = {m_particles.positions[i] + glm::vec2(+h.x, -h.y), col};
      v[2]          = {m_particles.positions[i] + glm::vec2(+h.x, +h.y), col};
      v[3]          = {m_particles.positions[i] + glm::vec2(-h.x, +h.y), col};

      m_vbo->bind();
      m_vbo->setData(v, 4 * sizeof(QuadVertex));
      Renderer::submit(m_shader, m_vao);

      ++m_alive;
    }
  }

  void BadParticleSystem::upload() {
    // m_ibo->setCount(0);
  }

  void BadParticleSystem::clear() {
    m_particles.active.clear();
    m_particles.positions.clear();
    m_particles.velocities.clear();
    m_particles.lifeTime.clear();
    m_particles.lifeRemaining.clear();
    m_particles.sizeBegin.clear();
    m_particles.sizeEnd.clear();
    m_particles.colourBegin.clear();
    m_particles.colourEnd.clear();

    m_alive = 0;
  }

  void BadParticleSystem::updateEmitter(ParticleEmitter &emitter, DeltaTime deltaTime) {
    float rate   = emitter.spawnRate;
    float period = 1.0f / glm::max(rate, 0.001f);

    emitter.emitAccumulator += deltaTime.seconds();
    while (emitter.emitAccumulator > period) {
      ParticleProps p = emitter.props;

      p.position  = emitter.pos;
      glm::vec2 v = sampleVelocityFromBase(emitter.props.velocity, emitter.vRand);
      p.velocity  = v;
      emit(p);
      emitter.emitAccumulator -= period;
    }
  }

  void BadParticleSystem::updateEmitters(std::vector<ParticleEmitter> &emitters,
                                         DeltaTime deltaTime) {
    for (auto &e : emitters) {
      updateEmitter(e, deltaTime);
    }
  }

} // namespace Zen
