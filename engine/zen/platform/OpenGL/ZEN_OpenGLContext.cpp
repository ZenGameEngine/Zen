#include <iostream>
#include <zen/platform/OpenGL/ZEN_OpenGLContext.h>

namespace Zen {
OpenGLContext::OpenGLContext(SDL_Window *window) : m_window(window) {
    ZEN_LOG_INFO("OpenGL context bound");
};

OpenGLContext::~OpenGLContext() { shutdown(); };

void OpenGLContext::init() {
    m_glContext = SDL_GL_CreateContext(m_window);
    ZEN_LOG_INFO("OpenGL context initialized");
};

void OpenGLContext::swapBuffers() { SDL_GL_SwapWindow(m_window); }

void OpenGLContext::shutdown() {
    if (m_glContext != nullptr) {
        SDL_GL_DestroyContext(m_glContext);
        m_glContext = nullptr;
        ZEN_LOG_INFO("OpenGL context destroyed");
    }
};
}; // namespace Zen