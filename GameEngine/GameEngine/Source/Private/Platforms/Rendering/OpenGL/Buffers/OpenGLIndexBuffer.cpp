#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLIndexBuffer.h"

// Third party
#include "glad/glad.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* const indexData, const uint32_t inCount)
{
	Count = inCount;
	glCreateBuffers(1, &IndexBufferHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), indexData, GL_STATIC_DRAW);
	UnBind();
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &IndexBufferHandle);
}

void OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
}

void OpenGLIndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}