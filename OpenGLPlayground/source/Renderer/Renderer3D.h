#pragma once

#include "glm/glm.hpp"
#include "Camera.h"

#include "Buffers.h"
#include "Shader.h"

class Renderer3D
{
public:
	static void Init();

	static void BeginScene(const PerspectiveCamera& camera);

	static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va, 
		const glm::mat4& model = glm::mat4(1.0f));

	static void EndScene();

private:
	
	struct SceneData
	{
		glm::mat4 m_ProjectionViewMatrix;
	};

	static SceneData s_SceneData;
};

