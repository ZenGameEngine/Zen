#include <glm/fwd.hpp>
#include <glm/gtc/random.hpp>
#include <zen/gui/ZEN_Style.h>
#include <zen/particles/ZEN_ParticleSystem.h>

namespace Zen {

  ParticleSystem::ParticleSystem(size_t maxParticles) : m_max(maxParticles) {
    m_particles.active.reserve(m_max);
    m_particles.active.assign(m_max, false);

    m_particles.positions.reserve(m_max);
    m_particles.positions.assign(m_max, glm::vec2(0));

    m_particles.velocities.reserve(m_max);
    m_particles.velocities.assign(m_max, glm::vec2(0));

    m_particles.lifeTime.reserve(m_max);
    m_particles.lifeTime.assign(m_max, 0.0f);

    m_particles.lifeRemaining.reserve(m_max);
    m_particles.lifeRemaining.assign(m_max, 0.0f);

    m_particles.sizeBegin.reserve(m_max);
    m_particles.sizeBegin.assign(m_max, glm::vec2(0));

    m_particles.sizeEnd.reserve(m_max);
    m_particles.sizeEnd.assign(m_max, glm::vec2(0));

    m_particles.colourBegin.reserve(m_max);
    m_particles.colourBegin.assign(m_max, glm::vec4(0));

    m_particles.colourEnd.reserve(m_max);
    m_particles.colourEnd.assign(m_max, glm::vec4(0));

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

  void ParticleSystem::emit(const ParticleProps &props) {
    m_particles.active[m_poolIndex]        = true;
    m_particles.positions[m_poolIndex]     = props.position;
    m_particles.velocities[m_poolIndex]    = props.velocity;
    m_particles.lifeTime[m_poolIndex]      = props.lifeTime;
    m_particles.lifeRemaining[m_poolIndex] = props.lifeTime;
    m_particles.sizeBegin[m_poolIndex]     = props.sizeBegin;
    m_particles.sizeEnd[m_poolIndex]       = props.sizeEnd;
    m_particles.colourBegin[m_poolIndex]   = props.colourBegin;
    m_particles.colourEnd[m_poolIndex]     = props.colourEnd;

    m_poolIndex = (m_poolIndex + 1) % m_particles.active.size();
  }

  void ParticleSystem::update(DeltaTime deltaTime) {
    float deltaTimef = deltaTime.seconds();
    m_alive          = 0;

    for (int i = 0; i < m_particles.active.size(); i++) {
      if (!m_particles.active[i]) {
        continue;
      }

      m_particles.lifeRemaining[i] -= deltaTimef;
      if (m_particles.lifeRemaining[i] <= 0.f) {
        m_particles.active[i] = false;
        continue;
      }

      m_particles.positions[i] += m_particles.velocities[i] * deltaTimef;

      float t        = 1.0f - (m_particles.lifeRemaining[i] / m_particles.lifeTime[i]);
      glm::vec2 size = glm::mix(m_particles.sizeBegin[i], m_particles.sizeEnd[i], t);
      glm::vec4 c    = glm::mix(m_particles.colourBegin[i], m_particles.colourEnd[i], t);

      glm::vec2 h(size * 0.5f);
      QuadVertex *v = &m_cpuQuad[m_alive * 4];
      v[0]          = {m_particles.positions[i] + glm::vec2(-h.x, -h.y), c};
      v[1]          = {m_particles.positions[i] + glm::vec2(+h.x, -h.y), c};
      v[2]          = {m_particles.positions[i] + glm::vec2(+h.x, +h.y), c};
      v[3]          = {m_particles.positions[i] + glm::vec2(-h.x, +h.y), c};

      ++m_alive;
    }
  }

  void ParticleSystem::upload() {
    const uint32_t &bytes = m_alive * 4 * sizeof(QuadVertex);
    m_vbo->bind();
    m_vbo->setData(m_cpuQuad.data(), bytes);
    m_ibo->setCount(m_alive * 6); // key line
  }

  void ParticleSystem::clear() {
    for (int i = 0; i < m_particles.active.size(); i++) {
      m_particles.active[i] = false;
    };

    m_alive = 0;
  }

  void ParticleSystem::updateEmitter(ParticleEmitter &emitter, DeltaTime deltaTime) {
    const float &rate   = emitter.spawnRate;
    const float &period = 1.0f / glm::max(rate, 0.001f);

    static Zen::ParticleProps particleProps = emitter.props;
    emitter.emitAccumulator += deltaTime.seconds();
    while (emitter.emitAccumulator > period) {
      particleProps          = emitter.props;
      particleProps.position = emitter.pos;

      const glm::vec2 &velocity = sampleVelocityFromBase(emitter.props.velocity, emitter.vRand);
      particleProps.velocity    = velocity;

      emit(particleProps);
      emitter.emitAccumulator -= period;
    }
  }

  void ParticleSystem::updateEmitters(std::vector<ParticleEmitter> &emitters, DeltaTime deltaTime) {
    for (auto &e : emitters) {
      updateEmitter(e, deltaTime);
    }
  }
} // namespace Zen
