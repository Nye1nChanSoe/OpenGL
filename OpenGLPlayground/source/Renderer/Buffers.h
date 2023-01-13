#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "Core.h"

enum class attrib: uint32_t
{
	ivec, ivec2, ivec3, ivec4,
	vec, vec2, vec3, vec4,
	mat2, mat3, mat4
};

/* To calculate offset and stride in bytes */
static uint32_t GetSizeFromType(attrib type)		
{
	switch (type)
	{
	case attrib::ivec:  return 4;
	case attrib::ivec2: return 4 * 2;
	case attrib::ivec3: return 4 * 3;
	case attrib::ivec4: return 4 * 4;
	case attrib::vec:   return 4;
	case attrib::vec2:  return 4 * 2;
	case attrib::vec3:  return 4 * 3;
	case attrib::vec4:  return 4 * 4;
	case attrib::mat2:  return 4 * 2 * 2;
	case attrib::mat3:  return 4 * 3 * 3;
	case attrib::mat4:  return 4 * 4 * 4;
	}

	glAssert(false, "Unknown glsl data type!");
	return NULL;
}

struct BufferElements
{
	attrib Type;
	uint32_t Size;
	bool Normalized;
	uint64_t Offset;
	std::string Name;

	BufferElements() { memset(this, 0, sizeof(*this)); }

	BufferElements(attrib type, const std::string& uniformName, bool normalized = false)
		: Type(type), Name(uniformName), Size(GetSizeFromType(type)), Normalized(normalized), Offset(0)
	{
	}

	int GetCountFromType() const
	{
		switch (Type)
		{
		case attrib::ivec:	return 1;
		case attrib::ivec2: return 2;
		case attrib::ivec3: return 2;
		case attrib::ivec4: return 2;
		case attrib::vec:   return 1;
		case attrib::vec2:  return 2;
		case attrib::vec3:  return 3;
		case attrib::vec4:  return 4;
		case attrib::mat2:  return 2 * 2;
		case attrib::mat3:  return 3 * 3;
		case attrib::mat4:  return 4 * 4;
		}

		glAssert(false, "Unknown glsl data type!");
		return NULL;
	}
};

class BufferLayout
{
public:
	BufferLayout()
		: m_Stride(0) {}

	BufferLayout(const std::initializer_list<BufferElements>& list)
		: m_BufferElements(list), m_Stride(0) 
	{
		CalculateStrideAndOffset();
	}

	~BufferLayout() = default;

	inline std::vector<BufferElements>& GetElements() { return m_BufferElements; }
	inline int GetStride() const { return m_Stride; }

	std::vector<BufferElements>::iterator begin() { return m_BufferElements.begin(); }
	std::vector<BufferElements>::iterator end() { return m_BufferElements.end(); }
	std::vector<BufferElements>::const_iterator begin() const { return m_BufferElements.begin(); }
	std::vector<BufferElements>::const_iterator end() const { return m_BufferElements.end(); }

private:
	void CalculateStrideAndOffset()
	{
		uint32_t offset = 0;
		for (auto& element : m_BufferElements)
		{
			element.Offset   = offset;
			offset		    += element.Size;
			m_Stride		+= element.Size;
		}
	}

private:
	uint32_t m_Stride;
	std::vector<BufferElements> m_BufferElements;
};

class VertexBuffer
{
public:
	VertexBuffer(float* data, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
	BufferLayout& GetLayout() { return m_Layout; }

	static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);

private:
	uint32_t m_RendererID;
	BufferLayout m_Layout;
};


class IndexBuffer
{
public:
	IndexBuffer(uint32_t* data, uint32_t index_count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline uint32_t GetCount() const { return m_Count; }

	static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t index_count);

private:
	uint32_t m_RendererID;
	uint32_t m_Count;
};


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
	void AddVertexBuffer(const VertexBuffer& vertexBuffer);
	void SetIndexBuffer(const IndexBuffer& indexBuffer);

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBufferRefs() const { return m_VertexBuffersRefs; }
	const std::shared_ptr<IndexBuffer>& GetIndexBufferRefs() const { return m_IndexBufferRef; }

	static std::shared_ptr<VertexArray> Create();

private:
	uint32_t m_RendererID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffersRefs;
	std::shared_ptr<IndexBuffer> m_IndexBufferRef;
};

