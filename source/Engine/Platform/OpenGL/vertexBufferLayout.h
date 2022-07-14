#pragma once

#include <vector>
#include <GL/glew.h>

#include "renderer.h"

struct vertexBufferElement
{
	unsigned int type;

	unsigned int count;

	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type);
};

class vertexBufferLayout
{
private:
	std::vector<vertexBufferElement> m_Elements;

	unsigned int m_Stride;

public:
	vertexBufferLayout() : m_Stride(0){};

	void PushFloat(unsigned int count);

	void PushUnsignedInt(unsigned int count);

	void PushUnsignedChar(unsigned int count);

	inline const std::vector<vertexBufferElement> getElements() const { return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }
};