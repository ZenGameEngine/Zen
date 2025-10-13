#include "QuadBuilder.h"
#include <ZEN_Shader.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

using namespace Zen;

void QuadBuilder::init(std::shared_ptr<Shader> shader) {

  m_shader = shader;

  m_vao.reset(VertexArray::Create());

  m_vbo.reset(VertexBuffer::Create(nullptr, sizeof(QuadVertex) * 4));
  m_vbo->setLayout({
      {ShaderDataType::Float2, "a_Position"},
      {ShaderDataType::Float4, "a_Color"   },
  });
  m_vao->addVertexBuffer(m_vbo);

  static const uint32_t kIndices[6] = {0, 1, 2, 2, 3, 0};

  m_ibo.reset(IndexBuffer::Create(const_cast<uint32_t *>(kIndices), 6));
  m_vao->setIndexBuffer(m_ibo);
}

void QuadBuilder::drawQuad(const glm::vec2 &position,
                           const glm::vec2 &size,
                           const glm::vec4 &colour) {
  const glm::vec2 h = 0.5f * size;

  QuadVertex verts[4] = {
      {{position.x - h.x, position.y - h.y}, colour},
      {{position.x + h.x, position.y - h.y}, colour},
      {{position.x + h.x, position.y + h.y}, colour},
      {{position.x - h.x, position.y + h.y}, colour},
  };

  m_vbo->setData(verts, sizeof(verts));

  m_shader->bind();
  Renderer::submit(m_shader, m_vao);
}
