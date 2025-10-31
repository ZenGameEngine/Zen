#include <zen/renderer/OpenGL/ZEN_OpenGLBuffer.h>
#include <zen/renderer/abstractions/ZEN_Buffer.h>
#include <zen/renderer/abstractions/ZEN_Renderer.h>

namespace Zen {
  VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {
    switch (Renderer::getAPI()) {
      case RendererAPI::API::None:
        ZEN_LOG_ERROR("[Zen/Renderer/Buffer] RendererAPI is not supported");
        return nullptr;

      case RendererAPI::API::OpenGL:
        ZEN_LOG_TRACE("[Zen/Renderer/Buffer] Vertex buffer: Using OpenGL RendererAPI");
        return new OpenGLVertexBuffer(vertices, size);
    }

    ZEN_LOG_ERROR("[Zen/Renderer/Buffer] Unknown RendererAPI");
    return nullptr;
  };

  IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t count) {
    switch (Renderer::getAPI()) {
      case RendererAPI::API::None:
        ZEN_LOG_ERROR("[Zen/Renderer/Buffer] RendererAPI is not supported");
        return nullptr;

      case RendererAPI::API::OpenGL:
        ZEN_LOG_TRACE("[Zen/Renderer/Buffer] Index buffer: Using OpenGL RendererAPI");
        return new OpenGLIndexBuffer(indices, count);
    }

    ZEN_LOG_ERROR("[Zen/Renderer/Buffer] Unknown RendererAPI");
    return nullptr;
  };
}; // namespace Zen
