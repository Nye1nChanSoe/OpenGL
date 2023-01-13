#pragma once

#include "Camera.h"

#include "Timestep.h"

#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

class OrthographicCameraController
{
public:
	OrthographicCameraController(float aspect, bool rotate = false);

	void OnUpdate(Timestep time);
	void OnEvent(Event& event);

	OrthographicCamera& GetCamera() { return m_Camera; }
	const OrthographicCamera& GetCamera() const { return m_Camera; }

	float GetZoomLevel() const { return m_ZoomLvl; }
	void SetZoomLevel(float level) { m_ZoomLvl = level; }

private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResize(WindowResizedEvent& e);

private:
	float m_Aspect;
	float m_ZoomLvl = 1.0f;
	OrthographicCamera m_Camera;

	bool m_Rotate;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRoation = 0.0f;
	float m_CameraTranslationSpeed = 3.0f;
	float m_CameraRotationSpeed = 120.0f;
};


class PerspectiveCameraController
{
public:
	PerspectiveCameraController(float fov, float aspectRatio, float near, float far, bool fpsMode = false);

	void OnUpdate(Timestep time);
	void OnEvent(Event& e);

	PerspectiveCamera& GetCamera() { return m_Camera; }
	const PerspectiveCamera& GetCamera() const { return m_Camera; }

private:
	bool OnMouseMove(MouseMovedEvent& e);
	bool OnMouseScroll(MouseScrolledEvent& e);

private:
	PerspectiveCamera m_Camera;
	float m_FOV = 45.0f;		// in degrees

	glm::vec3 m_CameraPosition = { 1.0f, 0.0f, 3.0f };
	glm::vec3 m_CameraFront = { 0.0f, 0.0f, -1.0f };
	float m_CameraSpeed = 2.5f;

	float m_LastX = 640.0f;
	float m_LastY = 360.0f;

	const float m_MouseSensitivity = 0.05f;

	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;

	bool m_FirstMouse = true;
	bool m_FpsMode;
};