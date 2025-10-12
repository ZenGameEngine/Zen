#include <zen/renderer/ZEN_RenderCommand.h>

#include <zen/platform/OpenGL/ZEN_OpenGLRendererAPI.h>

namespace Zen {
  RendererAPI *RenderCommand::s_rendererAPI = new OpenGLRendererAPI;
}; // namespace Zen