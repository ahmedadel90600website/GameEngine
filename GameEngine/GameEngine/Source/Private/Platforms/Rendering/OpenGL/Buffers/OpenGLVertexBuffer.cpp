#include "Public/PCH.h"

#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLVertexBuffer.h"

// Third party
#include "glad/glad.h"

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t sizeInBytes, const float* const vertexData)
{
	glCreateBuffers(1, &VertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, vertexData, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &VertexBufferHandle);
}

void OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferHandle);
}

void OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout& inLayput)
{
	Layout = inLayput;
}