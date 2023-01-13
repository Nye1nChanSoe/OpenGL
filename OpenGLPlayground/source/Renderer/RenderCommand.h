#pragma once

#include "glm/glm.hpp"
#include <memory>

#include "Buffers.h"

class RenderCommand
{
public:
	static void Clear();
	static void ClearColor(const glm::vec4& color);

	static void SetViewPort(int width, int height);

	/* Draw calls */
	static void DrawIndex(const std::shared_ptr<VertexArray>& va);

	static void DrawArray(int startingIndex, int count);
};