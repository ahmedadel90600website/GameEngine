#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLIndexBuffer.h"

// Third party
#include "glad/glad.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t sizeInBytes, const uint32_t* const indexData, uint32_t drawType)
{
	glCreateBuffers(1, &IndexBufferHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, indexData, drawType);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &IndexBufferHandle);
}

void OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
}

void OpenGLIndexBuffer::unBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}