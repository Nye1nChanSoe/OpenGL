#include "Renderer2D.h"
#include <glad/glad.h>

#include "RenderCommand.h"

Renderer2D::SceneData Renderer2D::s_SceneData;

void Renderer2D::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
	s_SceneData.m_ProjectionView = camera.GetProjectionViewMatrix();
}

void Renderer2D::BeginScene(const PerspectiveCamera& camera)
{
	s_SceneData.m_ProjectionView = camera.GetProjectionViewMatrix();
}


void Renderer2D::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va, const glm::mat4& modelMatrix)
{
	shader->Bind();
	va->Bind();

	shader->UploadUniformMat4("u_ProjectionView", s_SceneData.m_ProjectionView);
	shader->UploadUniformMat4("u_Model", modelMatrix);

	RenderCommand::DrawIndex(va);
 }

void Renderer2D::EndScene()
{
}


