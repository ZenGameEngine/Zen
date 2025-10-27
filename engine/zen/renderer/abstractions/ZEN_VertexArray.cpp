#include <zen/renderer/OpenGL/ZEN_OpenGLVertexArray.h>
#include <zen/renderer/abstractions/ZEN_Renderer.h>
#include <zen/renderer/abstractions/ZEN_VertexArray.h>

namespace Zen {

  VertexArray *VertexArray::Create() {
    switch (Renderer::getAPI()) {
      case RendererAPI::API::None:
        ZEN_LOG_ERROR("[Zen/Renderer/VertexArray] Renderer API is not supported");
        return nullptr;

      case RendererAPI::API::OpenGL:
        ZEN_LOG_TRACE("[Zen/Renderer/VertexArray] Vertex buffer: Using OpenGL renderer API");
        return new OpenGLVertexArray();
    }

    ZEN_LOG_CRITICAL("[Zen/Renderer/VertexArray] Unknown RendererAPI");
  };

}; // namespace Zen
