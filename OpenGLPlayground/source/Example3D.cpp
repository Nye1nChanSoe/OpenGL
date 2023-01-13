#include "Example3D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Renderer/KeyCodes.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer3D.h"

#include "Application.h"


Example3D::Example3D()
	: m_CameraController(glm::radians(45.0f), 1280.0f/720.0f, 0.1f, 100.0f, false)
{
	Application::GetApp().GetWindow().DisableCursor();

	//m_VertexArray = VertexArray::Create();

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,		// front square
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,		// back square
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,		// left square
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,		// right square
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,		// bottom square
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,		// top square
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f
	};

	//BufferLayout layout = {
	//	{attrib::vec3, "a_Position"},
	//	{attrib::vec2, "a_TexCoord"}
	//};

	//cubePositions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	//cubePositions[1] = glm::vec3(2.0f, 5.0f, -15.0f);
	//cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
	//cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
	//cubePositions[4] = glm::vec3(2.4f, -0.4f, -3.5f);
	//cubePositions[5] = glm::vec3(-1.7f, 3.0f, -7.5f);
	//cubePositions[6] = glm::vec3(1.3f, -2.0f, -2.5f);
	//cubePositions[7] = glm::vec3(1.5f, 2.0f, -2.5f);
	//cubePositions[8] = glm::vec3(1.5f, 0.2f, -1.5f);
	//cubePositions[9] = glm::vec3(-1.3f, 1.0f, -1.5f);

	//std::shared_ptr<VertexBuffer> vertexbuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	//vertexbuffer->Bind();
	//vertexbuffer->SetLayout(layout);

	//m_VertexArray->AddVertexBuffer(vertexbuffer);

	//m_Shader = Shader::Create("assets/shaders/shader3D.glsl");
	//m_Shader->UseProgram();

	//m_Texture = Texture2D::Create("assets/textures/Checkerboard.png");
	//m_Texture->BindTextureSlot(0);
	//m_Shader->UploadTextureUniform1i("u_Texture", 0);

	/// LightSource 
	m_LightSourceVA = VertexArray::Create();

	std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	{
		BufferLayout layout1 = {
			{attrib::vec3, "a_Positions"},
			{attrib::vec2, "a_TexCoords"},
			{attrib::vec3, "a_Normals"}
		};
		vertexBuffer->SetLayout(layout1);
	}
	m_LightSourceVA->AddVertexBuffer(vertexBuffer);

	m_LightSourceShader = Shader::Create("assets/shaders/lightSource.glsl");
	m_LightSourceShader->UseProgram();

	/// Cube 
	m_CubeVA = VertexArray::Create();

	std::shared_ptr<VertexBuffer> cubevertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	{
		BufferLayout layout2 = {
			{attrib::vec3, "a_Positions"},
			{attrib::vec2, "a_TexCoords"},
			{attrib::vec3, "a_Normals"}
		};
		cubevertexBuffer->SetLayout(layout2);
	}
	m_CubeVA->AddVertexBuffer(cubevertexBuffer);

	//m_CubeShader = Shader::Create("assets/shaders/GouraudLighting.glsl");
	m_CubeShader = Shader::Create("assets/shaders/lightingShader.glsl");
	m_CubeShader->UseProgram();
}

Example3D::~Example3D()
{
}

void Example3D::OnUpdate(Timestep ts)
{
	RenderCommand::Clear();
	RenderCommand::ClearColor({0.1f, 0.1f, 0.1f, 1.0f});

	m_CameraController.OnUpdate(ts);

	Renderer3D::BeginScene(m_CameraController.GetCamera());

	/// Object
	m_CubeShader->UseProgram();

	// Uniform materials
	m_CubeShader->UploadUniform3f("u_Material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	m_CubeShader->UploadUniform3f("u_Material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	m_CubeShader->UploadUniform3f("u_Material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	m_CubeShader->UploadUniform1f("u_Material.shininess", 32.0f);

	// Uniform light properties
	m_CubeShader->UploadUniform3f("u_Light.ambient", glm::vec3(0.2f));
	m_CubeShader->UploadUniform3f("u_Light.diffuse", glm::vec3(1.0f));
	m_CubeShader->UploadUniform3f("u_Light.specular", glm::vec3(0.5f));
	m_CubeShader->UploadUniform3f("u_Light.position", m_LightPos);

	m_CubeShader->UploadUniform3f("u_CameraPos", m_CameraController.GetCamera().GetCameraPosition());

	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(glm::mat4(1.0f))));
	m_CubeShader->UploadUniformMat3("u_NormalMatrix", normalMatrix);

	//float radius = 4.0f;
	//float moveX = static_cast<float>(std::cos(glfwGetTime() * 0.3f) * radius);
	//float moveZ = static_cast<float>(std::sin(glfwGetTime() * 0.3f) * radius);
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(moveX + 1.2f, 1.0f, moveZ - 2.0f));
	Renderer3D::Submit(m_CubeShader, m_CubeVA);


	/// Light Source
	m_LightSourceShader->UseProgram();
	m_LightSourceShader->UploadUniform3f("u_LightColor", glm::vec3(1.0f));

	glm::mat4 lightSourceModel = glm::translate(glm::mat4(1.0f), m_LightPos) *
		glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
	Renderer3D::Submit(m_LightSourceShader, m_LightSourceVA, lightSourceModel);


	Renderer3D::EndScene();
}

void Example3D::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);
}

