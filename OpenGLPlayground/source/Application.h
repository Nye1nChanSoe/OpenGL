#pragma once

#include "Platform/WindowsWindow.h"
#include <memory>

#include "Events/Event.h"
#include "Events/WindowEvent.h"

#include "LayerStack.h"


class Application
{
public:
	~Application();

	void Run();
	virtual void OnEvent(Event& e);

	virtual void PushLayer(Layer* layer);
	virtual void PopLayer(Layer* layer);
	virtual void PushOverlay(Layer* overlay);
	virtual void PopOverlay(Layer* overlay);

	static Application& GetApp() { return *s_App; }
	inline Window& GetWindow() { return *m_Window; }

private:
	bool OnWindowClose(WindowClosedEvent& event);
	bool OnWindowResize(WindowResizedEvent& event);

private:
	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;

	std::unique_ptr<Window> m_Window;
	
	LayerStack m_Layers;
	static Application* s_App;

protected:
	Application();
	Application(const Application& other) = delete;
};

Application* CreateApplication();
