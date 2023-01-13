#include "RenderCommand.h"
#include <glad/glad.h>

#include "Buffers.h"

void RenderCommand::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::ClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void RenderCommand::SetViewPort(int width, int height)
{
	glViewport(0, 0, width, height);
}

/* glDrawElements */
void RenderCommand::DrawIndex(const std::shared_ptr<VertexArray>& va)
{
	glDrawElements(GL_TRIANGLES, va->GetIndexBufferRefs()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void RenderCommand::DrawArray(int startingIndex, int count)
{
	glDrawArrays(GL_TRIANGLES, startingIndex, count);
}


