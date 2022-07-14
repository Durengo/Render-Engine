#pragma once

#include "renderer.h"

class texture
{
private:
	unsigned int m_RendererID;

	std::string m_filepath;

	unsigned char *m_LocalBuffer;

	int m_Width, m_Height, m_BPP;

public:
	texture(const std::string &path);

	~texture();

	void Bind(unsigned int slot = 0) const;

	void Unbind() const;

	inline int getWidth() const { return m_Width; }

	inline int getHeight() const { return m_Height; }
};