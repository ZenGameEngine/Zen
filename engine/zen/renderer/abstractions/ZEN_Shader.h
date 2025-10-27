#pragma once

#include <zen/utility/ZEN_Macros.h>
#include <zen/zen_pch.h>

namespace Zen {
  class Shader {
  public:
    Shader();
    ~Shader();

    bool init(const char *vertexPath, const char *fragmentPath);

    void bind() const;
    void unbind() const;
    void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

  private:
    uint32_t m_rendererID{0};
  };
} // namespace Zen
