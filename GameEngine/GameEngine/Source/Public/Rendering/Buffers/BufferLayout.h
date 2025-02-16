#pragma once
#include <string>
#include <stdint.h>

enum class EShaderDataType : uint8_t
{
	NONE,
	BOOL,
	INT, INT2, INT3, INT4,
	FLOAT, FLOAT2, FLOAT3, FLOAT4,
	MAT3, MAT4,
	MAX
};

struct BufferElement
{
	BufferElement(const std::string& name, const EShaderDataType dataType, bool isNormalized);

	// The number of elements of the buffer element. Example: Vec3 which is EShaderDataType::FLOAT3 will return 3,  EShaderDataType::FLOAT4 will return 4;
	uint32_t GetNumberOfElements() const;

	// FLOAT3 will be 3 * 4 = 12. FLOAT4 will be 16...etc
	uint32_t GetSize() const;

	std::string Name = "";
	uint16_t Offset = 0;
	EShaderDataType DataType = EShaderDataType::NONE;
	uint8_t bShouldNormalize : 1;
};

class BufferLayout
{
public:

	BufferLayout() {};
	BufferLayout(const std::vector<BufferElement>& inElements);

	inline const std::vector<BufferElement>& GetBufferElements() const { return BufferElements; }
	uint32_t GetStrideSize() const;

private:

	std::vector<BufferElement> BufferElements;
};