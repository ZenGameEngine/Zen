#include <zen/platform/OpenGL/ZEN_OpenGLBuffer.h>

namespace Zen {
  // Vertex Buffer
  OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
    glCreateBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_rendererID); }

  void OpenGLVertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); }
  void OpenGLVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

  void OpenGLVertexBuffer::setData(const void *data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  }

  // Index Buffer
  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : m_count(count) {
    glCreateBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &m_rendererID); }

  void OpenGLIndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
  void OpenGLIndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

  uint32_t OpenGLIndexBuffer::getCount() const {
    // ZEN_LOG_INFO("Index count: {}", m_count);
    return m_count;
  }

  void OpenGLIndexBuffer::setCount(uint32_t count) { m_count = count; }
} // namespace Zen