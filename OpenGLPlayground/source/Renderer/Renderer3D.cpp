#include "Renderer3D.h"

#include <glad/glad.h>
#include "RenderCommand.h"

Renderer3D::SceneData Renderer3D::s_SceneData;

void Renderer3D::Init()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer3D::BeginScene(const PerspectiveCamera& camera)
{
	s_SceneData.m_ProjectionViewMatrix = camera.GetProjectionViewMatrix();
}

void Renderer3D::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va, const glm::mat4& model)
{
	shader->Bind();
	va->Bind();

	shader->UploadUniformMat4("u_ProjectionView", s_SceneData.m_ProjectionViewMatrix);
	shader->UploadUniformMat4("u_Model", model);

	RenderCommand::DrawArray(0, 36);
}

void Renderer3D::EndScene()
{
}
