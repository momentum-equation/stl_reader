#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &RendererID_)); // buffer tied to a vertex array object
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID_)); // bind to array to be plotted
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // read in the buffer
}

VertexBuffer::~VertexBuffer(){
    GLCall(glDeleteBuffers(1, &RendererID_))
}

void VertexBuffer::Bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID_));
}

void VertexBuffer::Unbind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
