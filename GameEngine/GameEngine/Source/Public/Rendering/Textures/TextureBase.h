#pragma once

#include "stdint.h"

class TextureBase
{
public:

	virtual ~TextureBase() {};

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;
	virtual void Bind(const uint32_t slot = 0) const = 0;
	virtual void UnBind(const uint32_t slot = 0) const = 0;
};