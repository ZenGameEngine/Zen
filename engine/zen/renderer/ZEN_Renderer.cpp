#include <zen/renderer/ZEN_Renderer.h>

namespace Zen {
  Renderer::SceneData *Renderer::m_sceneData = new Renderer::SceneData;

  void Renderer::beginScene(const Camera &camera) {
    m_sceneData->ViewProjectionMatrix = camera.viewProjectionMatrix();
  }

  void Renderer::endScene() {}

  void Renderer::submit(const std::shared_ptr<Shader> &shader,
                        const std::shared_ptr<VertexArray> &vertexArray) {
    shader->bind();
    shader->uploadUniformMat4("u_viewProjection", m_sceneData->ViewProjectionMatrix);

    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
  }

}; // namespace Zen
