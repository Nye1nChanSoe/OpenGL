#pragma once

#include "Core.h"

#include <string>
#include <functional>

#include "Events/Event.h"
#include <GLFW/glfw3.h>


struct WindowProps
{
	int m_Width, m_Height;
	std::string m_Name;

	WindowProps()
		: m_Width(1280), m_Height(720), m_Name("Learn OpenGL")
	{
	}
};

class Window
{
	using EventCallback = std::function<void(Event&)>;
public:
	Window(const WindowProps& data = WindowProps());
	~Window();

	void Init(const WindowProps& data);
	void ShutDown();

	inline const int GetWidth() const { return m_WindowData.m_Width; }
	inline const int GetHeight() const { return m_WindowData.m_Height; }

	inline void SetEventCallback(EventCallback callback) { m_WindowData.m_EventCallback = callback; }

	inline GLFWwindow* GetNativeWindow() { return m_Window; }

	void SetVSync(bool sync);

	// Cursor modes 
	void DisableCursor();
	void EnableCursor(); 
	void HideCursor();

	// swap buffers and poll events
	void OnUpdate();

private:
	GLFWwindow* m_Window;

	struct WindowData
	{
		int m_Width = 0, m_Height = 0;
		std::string m_WindowName;

		bool m_Sync = false;
		EventCallback m_EventCallback;
	};

	WindowData m_WindowData;
};
