#include "Input.h"
#include "Application.h"

Input Input::s_Input;

bool Input::IsKeyPressedImpl(int keycode)
{
	auto* window = Application::GetApp().GetWindow().GetNativeWindow();
	int state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressedImpl(int button)
{
	auto* window = Application::GetApp().GetWindow().GetNativeWindow();
	int state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS || state == GLFW_RELEASE;
}

std::pair<float, float> Input::GetMousePosImpl()
{
	auto* window = Application::GetApp().GetWindow().GetNativeWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return { (float)xpos, (float)ypos };
}

float Input::GetMousePosXImpl()
{
	auto [xpos, ypos] = GetMousePosImpl();
	return xpos;
}

float Input::GetMousePosYImpl()
{
	auto [xpos, ypos] = GetMousePosImpl();
	return ypos;
}

