#include <zen/platform/OpenGL/ZEN_OpenGLVertexArray.h>
#include <zen/renderer/ZEN_Renderer.h>
#include <zen/renderer/ZEN_VertexArray.h>

namespace Zen {

  VertexArray *VertexArray::Create() {
    switch (Renderer::getAPI()) {
      case RendererAPI::API::None:
        ZEN_LOG_ERROR("Renderer API is not supported");
        return nullptr;

      case RendererAPI::API::OpenGL:
        ZEN_LOG_INFO("Vertex buffer: Using OpenGL renderer API");
        return new OpenGLVertexArray();
    }

    ZEN_LOG_ERROR("Unknown renderer API");
  };

}; // namespace Zen