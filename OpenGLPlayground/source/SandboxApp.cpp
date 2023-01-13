#include "Renderer/2DRenderer.h"
#include "Example3D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer")
		, m_CameraController(1280.0f / 720.0f)
	{
		m_SquareVA = VertexArray::Create();
		m_SquareVA->Bind();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f
		};

		/* Layout of vertex buffer */
		BufferLayout layout = {
			{attrib::vec3, "a_Position"},			// location = 0
			{attrib::vec2, "a_TexCoord"}			// location = 1
		};

		std::shared_ptr<VertexBuffer> m_SquareVB = VertexBuffer::Create(vertices, sizeof(vertices));
		m_SquareVB->SetLayout(layout);

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> m_SquareIB = IndexBuffer::Create(indices, 6);
	
		/* Store vertex buffer and index buffer inside vertex array */
		m_SquareVA->AddVertexBuffer(m_SquareVB);
		m_SquareVA->SetIndexBuffer(m_SquareIB);

		m_SquareShader = Shader::Create("assets/shaders/texture.glsl");
		m_SquareShader->UseProgram();

		m_CheckerBoardTex = Texture2D::Create("assets/textures/Checkerboard.png");
		m_CheckerBoardTex->BindTextureSlot(0);

		m_SquareShader->UploadTextureUniform1i("u_Texture", 0);


		/// Triangle
		m_TriangleVA = VertexArray::Create();
		m_TriangleVA->Bind();

		float vertices1[] = {
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		BufferLayout layout1 = {
			{attrib::vec3, "a_Position"},
			{attrib::vec3, "a_Color"}
		};

		std::shared_ptr<VertexBuffer> m_TriangleVB = VertexBuffer::Create(vertices1, sizeof(vertices1));
		m_TriangleVB->SetLayout(layout1);

		uint32_t indices1[] = {
			0, 1, 2
		};

		std::shared_ptr<IndexBuffer> m_TriangleIB = IndexBuffer::Create(indices1, 3);

		m_TriangleVA->AddVertexBuffer(m_TriangleVB);
		m_TriangleVA->SetIndexBuffer(m_TriangleIB);
		
		m_TriangleShader = Shader::Create("assets/shaders/triangle.glsl");
		m_TriangleShader->UseProgram();
	}

	~ExampleLayer()
	{
	}

	virtual void OnUpdate(Timestep time) 
	{
		m_CameraController.OnUpdate(time);

		RenderCommand::Clear();
		RenderCommand::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		
		Renderer2D::BeginScene(m_CameraController.GetCamera());

		float ro = (float)glfwGetTime();
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		//glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), ro, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 rotation = glm::mat4(1.0f);

		for (int i = 0; i < 5; ++i)			/// Squares 
		{
			for (int j = 0; j < 5; ++j)
			{
				glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(j * 0.11f, i * 0.11f, 0.0f));
				glm::mat4 transform = translation * rotation * scale;
				//Renderer2D::Submit(m_SquareShader, m_SquareVA, transform);
			}
		}
		Renderer2D::Submit(m_TriangleShader, m_TriangleVA);		/// Triangle

		Renderer2D::EndScene();
;	}

	virtual void OnEvent(Event& e) 
	{
		m_CameraController.OnEvent(e);
	}

private:
	std::shared_ptr<VertexArray> m_SquareVA;
	std::shared_ptr<VertexArray> m_TriangleVA;

	std::shared_ptr<Shader> m_SquareShader;
	std::shared_ptr<Shader> m_TriangleShader;

	std::shared_ptr<Texture2D> m_CheckerBoardTex;
	std::shared_ptr<Texture2D> m_ChernoLogoTex;

	OrthographicCameraController m_CameraController;
};


class SandBox : public Application
{
public:
	SandBox()
	{
		/// TODO: create a test system

		//PushLayer(new ExampleLayer);
		PushLayer(new Example3D);
	}

	~SandBox()
	{
	}
};

Application* CreateApplication()
{
	return new SandBox();
}