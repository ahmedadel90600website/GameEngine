#include "Public/PCH.h"

#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLVertexBuffer.h"

// Third party
#include "glad/glad.h"

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t sizeInBytes, const float* const vertexData, uint32_t drawType)
{
	glCreateBuffers(1, &VertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, vertexData, drawType);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &VertexBufferHandle);
}

void OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferHandle);
}

void OpenGLVertexBuffer::unBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}