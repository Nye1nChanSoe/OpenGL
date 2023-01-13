#pragma once

#include "Buffers.h"
#include "Shader.h"
#include "Camera.h"

#include <memory>
#include <glm/glm.hpp>


class Renderer2D
{
public:

	/* Enable some states */
	static void Init();

	/* Camera, lighting, environment */
	static void BeginScene(const OrthographicCamera& camera);
	static void BeginScene(const PerspectiveCamera& camera);

	/* Submit data to OpenGL */
	static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va, const glm::mat4& modelMatrix = glm::mat4(1.0f));

	static void EndScene();

private:
	struct SceneData
	{
		glm::mat4 m_ProjectionView;
	};

	static SceneData s_SceneData;
};

