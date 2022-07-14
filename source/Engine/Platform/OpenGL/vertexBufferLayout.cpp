#include "vertexBufferLayout.h"

unsigned int vertexBufferElement::getSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_FLOAT:
		return 4;
	case GL_UNSIGNED_INT:
		return 4;
	case GL_UNSIGNED_BYTE:
		return 1;
	}
	ASSERT(false);
	return 0;
}

void vertexBufferLayout::PushFloat(unsigned int count)
{
	m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
	m_Stride += count * vertexBufferElement::getSizeOfType(GL_FLOAT);
}

void vertexBufferLayout::PushUnsignedInt(unsigned int count)
{
	m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	m_Stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

void vertexBufferLayout::PushUnsignedChar(unsigned int count)
{
	m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	m_Stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
