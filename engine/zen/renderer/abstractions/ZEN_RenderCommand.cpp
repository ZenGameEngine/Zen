#include <zen/renderer/OpenGL/ZEN_OpenGLRendererAPI.h>
#include <zen/renderer/abstractions/ZEN_RenderCommand.h>

namespace Zen {
  RendererAPI *RenderCommand::s_rendererAPI = new OpenGLRendererAPI;
}; // namespace Zen
