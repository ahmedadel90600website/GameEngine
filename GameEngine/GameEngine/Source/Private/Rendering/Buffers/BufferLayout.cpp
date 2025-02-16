#include "Public/PCH.h"
#include "Public/Rendering/Buffers/BufferLayout.h"

// BufferElement ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BufferElement::BufferElement(const std::string& name, const EShaderDataType dataType, bool isNormalized) :
	Name(name),
	DataType(dataType),
	bShouldNormalize(isNormalized)

{
}

uint32_t BufferElement::GetNumberOfElements() const
{	
	if (DataType == EShaderDataType::BOOL || DataType == EShaderDataType::INT || DataType == EShaderDataType::FLOAT)
	{
		return 1;
	}

	if (DataType == EShaderDataType::INT2 || DataType == EShaderDataType::FLOAT2)
	{
		return 2;
	}

	if (DataType == EShaderDataType::INT3 || DataType == EShaderDataType::FLOAT3)
	{
		return 3;
	}

	if (DataType == EShaderDataType::INT4 || DataType == EShaderDataType::FLOAT4)
	{
		return 4;
	}

	if (DataType == EShaderDataType::MAT3)
	{
		return 3 * 3;
	}

	if (DataType == EShaderDataType::MAT4)
	{
		return 4 * 4;
	}

	GameEngine_Assert(false, "BufferElement::GetNumberOfElements(), type not supported.");
	return 0;
}

uint32_t BufferElement::GetSize() const
{
	if (DataType == EShaderDataType::NONE || DataType == EShaderDataType::MAX)
	{
		GameEngine_Assert(false, "BufferElement::GetSize(), you need to specify a type for DataType.");
		return 0;
	}

	return (DataType == EShaderDataType::BOOL ? 1 : 4) * GetNumberOfElements();
}
// BufferElement ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BufferLayout ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BufferLayout::BufferLayout(const std::vector<BufferElement>& inElements) :
	BufferElements(inElements)
{
	uint16_t currentOffset = 0;
	for (BufferElement& currentElement : BufferElements)
	{
		currentElement.Offset = currentOffset;
		currentOffset += currentElement.GetSize();
	}
}

uint32_t BufferLayout::GetStrideSize() const
{
	if (BufferElements.size() == 0)
	{
		GameEngine_Assert(false, "BufferLayout::GetStrideSize(), The layout is empty.");
		return 0;
	}

	uint8_t finalStrideSize = 0;
	for (const BufferElement& element : BufferElements)
	{
		finalStrideSize += element.GetSize();
	}

	return finalStrideSize;
}
// BufferLayout ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////