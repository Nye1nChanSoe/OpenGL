#include "CameraController.h"

#include "Input.h"
#include "KeyCodes.h"

#include "Core.h"


OrthographicCameraController::OrthographicCameraController(float aspect, bool rotate)
	: m_Aspect(aspect), m_Camera(-aspect * m_ZoomLvl, aspect * m_ZoomLvl, -aspect * m_ZoomLvl, aspect * m_ZoomLvl), m_Rotate(rotate)
{
}

void OrthographicCameraController::OnUpdate(Timestep time)
{
	if (Input::IsKeyPressed(GLFW_KEY_W))
		m_CameraPosition.y += m_CameraTranslationSpeed * time;
	else if (Input::IsKeyPressed(GLFW_KEY_S))
		m_CameraPosition.y -= m_CameraTranslationSpeed * time;

	if (Input::IsKeyPressed(GLFW_KEY_A))
		m_CameraPosition.x -= m_CameraTranslationSpeed * time;
	else if (Input::IsKeyPressed(GLFW_KEY_D))
		m_CameraPosition.x += m_CameraTranslationSpeed * time;

	if (m_Rotate)
	{
		if (Input::IsKeyPressed(GLFW_KEY_Q))
			m_CameraRoation += m_CameraRotationSpeed * time;
		else if (Input::IsKeyPressed(GLFW_KEY_E))
			m_CameraRoation -= m_CameraRotationSpeed * time;

		m_Camera.SetCameraRotation(m_CameraRoation);
	}

	/* The higher the zoom level the faster the camera speed */
	m_CameraTranslationSpeed = m_ZoomLvl * 3.0f; 

	m_Camera.SetCameraPosition(m_CameraPosition);
}

void OrthographicCameraController::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLvl -= e.GetYOffset() * 0.25f;
	m_ZoomLvl = std::max(m_ZoomLvl, 0.25f);
	m_ZoomLvl = std::min(m_ZoomLvl, 3.0f);
	m_Camera.SetProjectionMatrix(-m_Aspect * m_ZoomLvl, m_Aspect * m_ZoomLvl, -m_Aspect * m_ZoomLvl, m_Aspect * m_ZoomLvl);

	return false;
}

bool OrthographicCameraController::OnWindowResize(WindowResizedEvent& e)
{
	m_Aspect = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjectionMatrix(-m_Aspect * m_ZoomLvl, m_Aspect * m_ZoomLvl, -m_Aspect * m_ZoomLvl, m_Aspect * m_ZoomLvl);

	return false;
}


PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, float near, float far, bool fpsMode)
	: m_Camera(fov, aspectRatio, near, far), m_FpsMode(fpsMode)
{
}

void PerspectiveCameraController::OnUpdate(Timestep time)
{
	if (Input::IsKeyPressed(GLFW_KEY_W))
		m_CameraPosition += m_CameraSpeed * m_CameraFront * time.GetSeconds();
	else if (Input::IsKeyPressed(GLFW_KEY_S))
		m_CameraPosition -= m_CameraSpeed * m_CameraFront * time.GetSeconds();

	if (Input::IsKeyPressed(GLFW_KEY_A))
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * m_CameraSpeed * time.GetSeconds();
	else if (Input::IsKeyPressed(GLFW_KEY_D))
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * m_CameraSpeed * time.GetSeconds();

	/* xz plane fps camera */
	if (m_FpsMode)
		m_CameraPosition.y = 0.0f;

	m_Camera.SetCameraPosition(m_CameraPosition);
}

void PerspectiveCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseMove));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseScroll));
}

bool PerspectiveCameraController::OnMouseMove(MouseMovedEvent& e)
{
	float xpos = e.GetXPos();
	float ypos = e.GetYPos();

	if (m_FirstMouse)
	{
		m_LastX = xpos;
		m_LastY = ypos;
		m_FirstMouse = false;
	}

	float xoffset = xpos - m_LastX;
	float yoffset = m_LastY - ypos;		// reversed since y coordinate range from bottom to top
	m_LastX = xpos;
	m_LastY = ypos;

	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	m_Pitch = std::max(m_Pitch, -89.0f);
	m_Pitch = std::min(m_Pitch, 89.0f);

	glm::vec3 direction;
	direction.x = static_cast<float>(std::cos(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch)));
	direction.y = static_cast<float>(std::sin(glm::radians(m_Pitch)));
	direction.z = static_cast<float>(std::sin(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch)));

	m_CameraFront = glm::normalize(direction);
	m_Camera.SetCameraFront(m_CameraFront);

	return false;
}

bool PerspectiveCameraController::OnMouseScroll(MouseScrolledEvent& e)
{
	m_FOV -= e.GetYOffset();

	m_FOV = std::max(m_FOV, 1.0f);
	m_FOV = std::min(m_FOV, 45.0f);

	m_Camera.SetProjectionMatrix(glm::radians(m_FOV), 1280.0f / 720.0f, 0.1f, 100.0f);

	return false;
}




