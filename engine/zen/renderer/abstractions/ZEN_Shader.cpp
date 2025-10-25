#include <zen/renderer/abstractions/ZEN_Shader.h>

// Helper functions
namespace {
  void loadShaderCode(const char *vertexPath,
                      std::string *vertexCode,
                      const char *fragmentPath,
                      std::string *fragmentCode) {

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
      // open files
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;

      // read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();

      // close file handlers
      vShaderFile.close();
      fShaderFile.close();

      // convert stream into string
      *vertexCode   = vShaderStream.str();
      *fragmentCode = fShaderStream.str();
    } catch (const std::ifstream::failure &e) {
      ZEN_LOG_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
      throw std::runtime_error("shader file read failed");
    }
  };

  bool compileShader(const uint32_t shaderId, const char *shaderCode) {
    GLint isCompiled = 0;
    bool isOk        = true;

    glShaderSource(shaderId, 1, &shaderCode, nullptr);

    // Compile the vertex shader
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled != GL_FALSE) {
      return isOk;
    }

    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    GLchar *errorData = new GLchar[maxLength];
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, errorData);

    // We don't need the shader anymore.
    glDeleteShader(shaderId);
    ZEN_LOG_ERROR("[Zen/Renderer/Shader] {}", errorData);

    delete[] errorData;
    return !isOk;
  };

  bool
  linkShaders(const uint32_t programID, const uint32_t vertShaderID, const uint32_t fragShaderID) {
    bool isOk = true;

    // Attach our shaders to our program
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);

    // Link our program
    glLinkProgram(programID);

    // Note the different functions here: glGetProgram instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
    if (isLinked != GL_FALSE) {
      // Always detach shaders after a successful link.
      glDetachShader(programID, vertShaderID);
      glDetachShader(programID, fragShaderID);
      ZEN_LOG_DEBUG("[Zen/Renderer/Shader] Shader Program #{}, linked successfully!", programID);
      return isOk;
    };

    GLint maxLength = 0;
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    GLchar *errorData = new GLchar[maxLength];
    glGetProgramInfoLog(programID, maxLength, &maxLength, errorData);

    // We don't need the program anymore.
    glDeleteProgram(programID);

    // Don't leak shaders either.
    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);

    // We don't need the shader anymore.
    ZEN_LOG_ERROR("[Zen/Renderer/Shader] {}", errorData);
    delete[] errorData;

    return !isOk;
  };
}; // namespace

namespace Zen {
  Shader::Shader() { ZEN_LOG_INFO("[Zen/Renderer/Shader] Constructing Shader #{}", m_rendererID); };

  Shader::~Shader() {
    glDeleteProgram(m_rendererID);
    ZEN_LOG_INFO("[Zen/Renderer/Shader] Shader #{} deconstructed", m_rendererID);
  }

  bool Shader::init(const char *vertexPath, const char *fragmentPath) {
    bool isOk = true;
    // Read our shaders into the appropriate buffers
    // Create an empty vertex shader handle
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode, fragmentCode;
    loadShaderCode(vertexPath, &vertexCode, fragmentPath, &fragmentCode);

    const char *vertShaderCode = vertexCode.c_str();
    const char *fragShaderCode = fragmentCode.c_str();

    uint32_t vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!compileShader(vertexShader, vertShaderCode)) {
      ZEN_LOG_ERROR("[Zen/Renderer/Shader] Failed to compile vertex shader");
      return !isOk;
    };

    // Create an empty fragment shader handle
    uint32_t fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!compileShader(fragmentShader, fragShaderCode)) {
      ZEN_LOG_ERROR("[Zen/Renderer/Shader] Failed to compile fragment shader");
      return !isOk;
    };

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    m_rendererID = glCreateProgram();
    if (!linkShaders(m_rendererID, vertexShader, fragmentShader)) {
      ZEN_LOG_ERROR("[Zen/Renderer/Shader] Failed to link vertex & fragment shaders for Shader #{}",
                    m_rendererID);
      return !isOk;
    };

    ZEN_LOG_INFO("[Zen/Renderer/Shader] Shader #{} constructed successfully!", m_rendererID);
    return isOk;
  }

  void Shader::bind() const {
    glUseProgram(m_rendererID);
    ZEN_LOG_TRACE("[Zen/Renderer/Shader] Shader #{} binded!", m_rendererID);
  }

  void Shader::unbind() const {
    glUseProgram(0);
    ZEN_LOG_TRACE("[Zen/Renderer/Shader] Shader #{} unbinded!", m_rendererID);
  }

  void Shader::uploadUniformMat4(const std::string &name, const glm::mat4 &matrix) {
    GLint location = glGetUniformLocation(m_rendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  }
}; // namespace Zen
