#include <zen/renderer/ZEN_Buffer.h>

#include <zen/platform/OpenGL/ZEN_OpenGLBuffer.h>
#include <zen/renderer/ZEN_Renderer.h>

namespace Zen {
VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {
    switch (Renderer::getAPI()) {
    case RendererAPI::API::None:
        ZEN_LOG_ERROR("Renderer API is not supported");
        return nullptr;

    case RendererAPI::API::OpenGL:
        ZEN_LOG_TRACE("Vertex buffer: Using OpenGL renderer API");
        return new OpenGLVertexBuffer(vertices, size);
    }

    ZEN_LOG_ERROR("Unknown renderer API");
};

IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t count) {
    switch (Renderer::getAPI()) {
    case RendererAPI::API::None:
        ZEN_LOG_ERROR("Renderer API is not supported");
        return nullptr;

    case RendererAPI::API::OpenGL:
        ZEN_LOG_TRACE("Index buffer: Using OpenGL renderer API");
        return new OpenGLIndexBuffer(indices, count);
    }

    ZEN_LOG_ERROR("Unknown renderer API");
};
}; // namespace Zen