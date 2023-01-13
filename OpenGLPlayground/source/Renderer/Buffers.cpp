#include "Buffers.h"

#include <glad/glad.h>
#include <iostream>

// --------------------- Vertex buffers ------------------------- //
VertexBuffer::VertexBuffer(float* data, uint32_t size)
	: m_RendererID(0)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size)
{
	return std::make_shared<VertexBuffer>(data, size);
}

// --------------------- Index buffers ------------------------- //
IndexBuffer::IndexBuffer(uint32_t* data, uint32_t index_count)
	: m_RendererID(0), m_Count(index_count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t index_count)
{
	return std::make_shared<IndexBuffer>(data, index_count);
}


// --------------------- Vertex Arrays ------------------------- //
static GLenum ShaderTypeToOpenGLType(attrib type)
{
	switch (type)
	{
	case attrib::ivec:  return GL_INT;
	case attrib::ivec2:	return GL_INT;
	case attrib::ivec3: return GL_INT;
	case attrib::ivec4:	return GL_INT;
	case attrib::vec:	return GL_FLOAT;
	case attrib::vec2:  return GL_FLOAT;
	case attrib::vec3:  return GL_FLOAT;
	case attrib::vec4:  return GL_FLOAT;
	case attrib::mat2:  return GL_FLOAT;
	case attrib::mat3:  return GL_FLOAT;
	case attrib::mat4:  return GL_FLOAT;
	}

	glAssert(false, "Unknown glsl data type!");
	return NULL;
}


VertexArray::VertexArray()
	: m_RendererID(0)
{
	glCreateVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glAssert(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer doesn't have a layout!");
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	auto& layout = vertexBuffer->GetLayout();
	int index = 0;

	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			element.GetCountFromType(),
			ShaderTypeToOpenGLType(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE, 
			layout.GetStride(),
			(const void*)element.Offset
		);
		index++;
	}
	m_VertexBuffersRefs.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer)
{
	glBindVertexArray(m_RendererID);
	indexbuffer->Bind();

	m_IndexBufferRef = indexbuffer;
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer)
{
}

void VertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer)
{
}

std::shared_ptr<VertexArray> VertexArray::Create()
{
	return std::make_shared<VertexArray>();
}
