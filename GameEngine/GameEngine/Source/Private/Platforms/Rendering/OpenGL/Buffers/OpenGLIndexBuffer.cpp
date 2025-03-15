#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLIndexBuffer.h"
#include "Public/Profiler/Instrumentor.h"

// Third party
#include "glad/glad.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* const indexData, const uint32_t inCount)
{
	RENDERER_PROFILE_FUNCTION();

	Count = inCount;
	glCreateBuffers(1, &IndexBufferHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), indexData, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	RENDERER_PROFILE_FUNCTION();

	glDeleteBuffers(1, &IndexBufferHandle);
}

void OpenGLIndexBuffer::Bind() const
{
	RENDERER_PROFILE_FUNCTION();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
}

void OpenGLIndexBuffer::UnBind() const
{
	RENDERER_PROFILE_FUNCTION();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}