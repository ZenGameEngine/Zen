#include <glm/gtc/random.hpp>
#include <zen/particles/ZEN_ParticleSystem.h>

namespace Zen {

  ParticleSystem::ParticleSystem(size_t maxParticles) : m_max(maxParticles) {

    m_pool.resize(m_max);
    m_cpuQuad.resize(m_max * 4);

    // geometry setup
    m_vao.reset(VertexArray::Create());

    // dynamic vertex buffer (positions + colors), sized for the full pool
    m_vbo.reset(VertexBuffer::Create(nullptr,
                                     static_cast<uint32_t>(m_cpuQuad.size() * sizeof(QuadVertex))));
    m_vbo->setLayout({
        {ShaderDataType::Float2, "a_Position"},
        {ShaderDataType::Float4, "a_Color"   }
    });

    m_vao->addVertexBuffer(m_vbo);

    std::vector<uint32_t> indices;
    indices.reserve(m_max * 6);
    for (uint32_t i = 0; i < m_max; ++i) {
      uint32_t b = i * 4;
      indices.push_back(b + 0);
      indices.push_back(b + 1);
      indices.push_back(b + 2);
      indices.push_back(b + 2);
      indices.push_back(b + 3);
      indices.push_back(b + 0);
    }
    m_ibo.reset(IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size())));
    m_vao->setIndexBuffer(m_ibo);

    m_shader = std::make_shared<Shader>("data/particle.vert", "data/particle.frag");

    const glm::vec2 deadPos(0.0f);
    const glm::vec4 deadCol(0.0f);
    for (uint32_t i = 0; i < m_max; ++i) {
      QuadVertex *v = &m_cpuQuad[i * 4];
      v[0] = v[1] = v[2] = v[3] = {deadPos, deadCol};
    }

    m_vbo->bind();
    m_vbo->setData(m_cpuQuad.data(), static_cast<uint32_t>(m_cpuQuad.size() * sizeof(QuadVertex)));
  }

  void ParticleSystem::emit(const ParticleProps &p) {
    Particle &particle     = m_pool[m_poolIndex];
    particle.active        = true;
    particle.pos           = p.position;
    particle.vel           = p.velocity;
    particle.lifeTime      = p.lifeTime;
    particle.lifeRemaining = p.lifeTime;
    particle.sizeBegin     = p.sizeBegin;
    particle.sizeEnd       = p.sizeEnd;
    particle.colourBegin   = p.colourBegin;
    particle.colourEnd     = p.colourEnd;

    m_poolIndex = (m_poolIndex + 1) % m_pool.size();
  }

  void ParticleSystem::update(DeltaTime deltaTime) {
    float deltaTimef = deltaTime.seconds();
    m_alive          = 0;

    for (auto &p : m_pool) {
      if (!p.active) {
        continue;
      }

      p.lifeRemaining -= deltaTimef;
      if (p.lifeRemaining <= 0.f) {
        p.active = false;
        continue;
      }

      p.pos += p.vel * deltaTimef;

      float t     = 1.0f - (p.lifeRemaining / p.lifeTime);
      float size  = glm::mix(p.sizeBegin, p.sizeEnd, t);
      glm::vec4 c = glm::mix(p.colourBegin, p.colourEnd, t);

      glm::vec2 h(size * 0.5f);
      QuadVertex *v = &m_cpuQuad[m_alive * 4];
      v[0]          = {p.pos + glm::vec2(-h.x, -h.y), c};
      v[1]          = {p.pos + glm::vec2(+h.x, -h.y), c};
      v[2]          = {p.pos + glm::vec2(+h.x, +h.y), c};
      v[3]          = {p.pos + glm::vec2(-h.x, +h.y), c};

      ++m_alive;
    }
  }

  void ParticleSystem::upload() {
    const uint32_t bytes = m_alive * 4 * sizeof(QuadVertex);
    m_vbo->bind();
    m_vbo->setData(m_cpuQuad.data(), bytes);
    m_ibo->setCount(m_alive * 6); // key line
  }

  void ParticleSystem::clear() {
    for (auto &p : m_pool)
      p.active = false;

    m_alive = 0;
  }

  void ParticleSystem::updateEmitter(ParticleEmitter &emitter, DeltaTime deltaTime) {
    float rate   = emitter.spawnRate;
    float period = 1.0f / glm::max(rate, 0.001f);

    emitter.emitAccumulator += deltaTime.seconds();
    while (emitter.emitAccumulator > period) {
      Zen::ParticleProps p = emitter.props;

      p.position  = emitter.pos;
      glm::vec2 v = sampleVelocityFromBase(emitter.props.velocity, emitter.vRand);
      p.velocity  = v;
      emit(p);
      emitter.emitAccumulator -= period;
    }
  }

  void ParticleSystem::updateEmitters(std::vector<ParticleEmitter> &emitters, DeltaTime deltaTime) {
    for (auto &e : emitters) {
      updateEmitter(e, deltaTime);
    }
  }
} // namespace Zen