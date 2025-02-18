#include "Public/PCH.h"

#include "Public/Rendering/Buffers/BufferLayout.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLVertexArray.h"
#include "Public/Core.h"

// Third party
#include "glad/glad.h"

OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &Handle);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	UnBind();
}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(Handle);
}

void OpenGLVertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::BindVertexBuffer(const TSharedPtr<VertexBuffer>& inVertexBuffer)
{
	VertexBuffer* const inVertexBufferRaw = inVertexBuffer.get();
	GameEngine_Assert(inVertexBufferRaw != nullptr, "OpenGLVertexArray::BindVertexBuffer. Invalid index buffer passed.");

	VertexBuffer& inVertexBufferRef = *inVertexBufferRaw;
	const BufferLayout& layout = inVertexBufferRef.GetLayout();
	const std::vector<BufferElement>& bufferElements = layout.GetBufferElements();
	const uint16_t bufferElementsCount = static_cast<uint16_t>(bufferElements.size());
	GameEngine_Assert(bufferElementsCount != 0, "OpenGLVertexArray::BindVertexBuffer. Index buffer has no layout.");

	Bind();
	inVertexBufferRef.Bind();
	for (uint16_t i = 0; i < bufferElementsCount; ++i)
	{
		const BufferElement& currentAttribute = bufferElements[i];
		glEnableVertexAttribArray(i);
		// GL_FLOAT should be converted from EShaderDataType
		glVertexAttribPointer(i, currentAttribute.GetNumberOfElements(), GL_FLOAT, currentAttribute.bShouldNormalize, layout.GetStrideSize(), (const void*)(currentAttribute.Offset));
	}

	VertexBuffers.push_back(inVertexBuffer);
}

void OpenGLVertexArray::BindIndexBuffer(const TSharedPtr<IndexBuffer>& inIndexBuffer)
{
	GameEngine_Assert(inIndexBuffer.get() != nullptr, "Invalid index buffer passed.");
	TheIndexBuffer = inIndexBuffer;
	Bind();
	TheIndexBuffer->Bind();
}