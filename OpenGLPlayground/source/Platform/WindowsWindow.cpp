#include "WindowsWindow.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <glad/glad.h>

static int GLFWinitialized = false;

static void glfwCheckError(int errorCode, const char* description)
{
	ERROR("Error: %d, '%s'", errorCode, description);
}

Window::Window(const WindowProps& data)
{
	Init(data);
}

Window::~Window()
{
	ShutDown();
}

void Window::Init(const WindowProps& data)
{
	m_WindowData.m_Width = data.m_Width;
	m_WindowData.m_Height = data.m_Height;
	m_WindowData.m_WindowName = data.m_Name;


	INFO("Window Created: (%d, %d)", data.m_Width, data.m_Height);

	if (!GLFWinitialized)
	{
		int result = glfwInit();
		glAssert(result, "Failed to initialized GLFW!\n");

		glfwSetErrorCallback(glfwCheckError);
		GLFWinitialized = true;
	}

	m_Window = glfwCreateWindow(data.m_Width, data.m_Height, data.m_Name.c_str(), nullptr, nullptr);
	glAssert(m_Window, "Failed to create a window!\n");

	glfwMakeContextCurrent(m_Window);
	SetVSync(true);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glAssert(status, "Failed to initialize glad!");
	glfwSetWindowUserPointer(m_Window, &m_WindowData);

	INFO("Vendor:   %s", (const char*)glGetString(GL_VENDOR));
	INFO("Renderer: %s", (const char*)glGetString(GL_RENDERER));
	INFO("Version:  %s\n", (const char*)glGetString(GL_VERSION));

	// TODO: Set Callbacks ...
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowClosedEvent event;
			data.m_EventCallback(event);
		}
	);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.m_Width = width;
			data.m_Height = height;

			WindowResizedEvent event(width, height);
			data.m_EventCallback(event);
		}
	);

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keycode, int scancode, int action, int mod)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(keycode);
					data.m_EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyRepeatEvent event(keycode, 1);
					data.m_EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(keycode);
					data.m_EventCallback(event);
					break;
				}
			}
		}
	);

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xpos, (float)ypos);
			data.m_EventCallback(event);
		}
	);

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mod)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.m_EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.m_EventCallback(event);
				break;
			}
			}
		}
	);

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.m_EventCallback(event);
		}
	);

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(codepoint);
			data.m_EventCallback(event);
		}
	);
}

void Window::ShutDown()
{
	glfwTerminate();
}

void Window::OnUpdate()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::SetVSync(bool sync)
{
	glfwSwapInterval(sync);
	m_WindowData.m_Sync = sync;
}

void Window::DisableCursor() 
{ 
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

void Window::EnableCursor() 
{ 
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
}

void Window::HideCursor() 
{ 
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); 
}
