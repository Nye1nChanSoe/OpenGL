#include "Application.h"
#include "Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Renderer3D.h"
#include "Timestep.h"

#include "Input.h"


Application* Application::s_App = nullptr;

#define BIND(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	glAssert(!s_App, "Application can be created only once!");
	s_App = this;

	m_Window = std::unique_ptr<Window>(new Window());
	m_Window->SetEventCallback(BIND(OnEvent));

	Renderer2D::Init();
	Renderer3D::Init();
}

Application::~Application()
{

}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowClosedEvent>(BIND(OnWindowClose));
	dispatcher.Dispatch<WindowResizedEvent>(BIND(OnWindowResize));

	/* Events are propagated from the top to bottom layer */
	for (auto it = m_Layers.end(); it != m_Layers.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.m_Handled)	
			break;
	}
}

void Application::PushLayer(Layer* layer)
{
	m_Layers.PushLayer(layer);
	layer->OnAttach();
}

void Application::PopLayer(Layer* layer)
{
	m_Layers.PopLayer(layer);
	layer->OnDetach();
}

void Application::PushOverlay(Layer* overlay)
{
	m_Layers.PushOverlay(overlay);
	overlay->OnAttach();
}

void Application::PopOverlay(Layer* overlay)
{
	m_Layers.PopOverlay(overlay);
	overlay->OnDetach();
}

void Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		Timestep deltaTime = time - m_LastFrameTime;
		m_LastFrameTime = time;

		if (!m_Minimized)
		{
			/* Layers are updated from the bottom to top layer */
			for (auto* layer : m_Layers)
				layer->OnUpdate(deltaTime);
		}

		m_Window->OnUpdate();

		if(Input::IsKeyPressed(GLFW_KEY_ESCAPE))
			m_Running = false;
	}
}

bool Application::OnWindowClose(WindowClosedEvent& event)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizedEvent& event)
{
	if (event.GetWidth() == 0 || event.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	RenderCommand::SetViewPort(event.GetWidth(), event.GetHeight());
	m_Minimized = false;
	return false;
}

