#pragma once

#include <string>
#include <memory>

class Texture2D
{
public:
	Texture2D(const std::string& filepath);
	~Texture2D();

	void Bind(unsigned int slot = 0) const;
	void BindTextureSlot(unsigned int slot = 0) const;
	void UnBind(unsigned int slot = 0) const;

	static std::shared_ptr<Texture2D> Create(const std::string& filepath);

private:
	unsigned int m_RendererID;
	uint32_t m_Width, m_Height;
	std::string m_Path;
};
