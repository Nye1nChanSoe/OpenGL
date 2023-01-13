#include "Texture2D.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "Core.h"


Texture2D::Texture2D(const std::string& filepath)
	: m_RendererID(0), m_Width(0), m_Height(0), m_Path(filepath)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

	int width, height, bits_per_pixel;
	stbi_uc* image_data = stbi_load(filepath.c_str(), &width, &height, &bits_per_pixel, 0);
	glAssert(image_data, "Failed to load image!");

	int internalFormat = 0;   // internal format is the OpenGL format
	int externalFormat = 0;   // external format is the image format

	/* Check alpha value is specified or not */
	if (bits_per_pixel == 4)
	{
		internalFormat = GL_RGBA8;
		externalFormat = GL_RGBA;
	}
	else if (bits_per_pixel == 3)
	{
		internalFormat = GL_RGB8;
		externalFormat = GL_RGB;
	}
	glAssert((internalFormat & externalFormat), "Unspecified image format!");

	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);

	// Specify storage for all levels of a two dimensional texture array
	glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);   // // 1 - Specify the number of texture levels.

	// Texture settings 
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Specify two dimensional texture image
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, externalFormat, GL_UNSIGNED_BYTE, image_data); // Level 0 is the base image level.

	stbi_image_free(image_data);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture2D::Bind(unsigned int slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

void Texture2D::BindTextureSlot(unsigned int slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

void Texture2D::UnBind(unsigned int slot) const
{
	glBindTextureUnit(slot, 0);
}

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath)
{
	return std::make_shared<Texture2D>(filepath);
}
