#pragma once

#include "Layer.h"
#include "Timestep.h"

#include "Events/Event.h"
#include "Events/MouseEvent.h"

#include "Renderer/Buffers.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture2D.h"
#include "Renderer/CameraController.h"

class Example3D: public Layer
{
public:
	Example3D();
	virtual ~Example3D();

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(Event& e) override;

private:
	//std::shared_ptr<VertexArray> m_VertexArray;
	//std::shared_ptr<Shader> m_Shader;
	//std::shared_ptr<Texture2D> m_Texture;

	std::shared_ptr<VertexArray> m_LightSourceVA;
	std::shared_ptr<Shader> m_LightSourceShader;
	glm::vec3 m_LightPos = { 1.2f, 1.0f, -2.0f };		// position of light source

	std::shared_ptr<VertexArray> m_CubeVA;
	std::shared_ptr<Shader> m_CubeShader;

	PerspectiveCameraController m_CameraController;

	glm::vec3 cubePositions[10];
};
