#pragma once

#include <glm/glm.hpp>


class OrthographicCamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);

	void SetProjectionMatrix(float left, float right, float bottom, float top);

	const glm::vec3& GetCameraPosition() const { return m_CameraPosition; }
	void SetCameraPosition(const glm::vec3& position) { m_CameraPosition = position; RecalculateCameraMatrices(); }

	float GetCameraRotation() const { return m_CameraRotation; }
	void SetCameraRotation(const float& rotation) { m_CameraRotation = rotation; RecalculateCameraMatrices(); }

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

private:
	void RecalculateCameraMatrices();

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionViewMatrix;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;
};

class PerspectiveCamera
{
public:
	PerspectiveCamera(float fov, float apsectRatio, float near, float far);

	void SetProjectionMatrix(float fov, float aspectRatio, float near, float far);

	const glm::vec3& GetCameraFront() const { return m_CameraFront; }
	void SetCameraFront(const glm::vec3& front) { m_CameraFront = front; RecalculatePosition(); }

	const glm::vec3& GetCameraPosition() const { return m_CameraPosition; }
	void SetCameraPosition(const glm::vec3& position) { m_CameraPosition = position; RecalculatePosition(); }

	const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4 GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

private:
	void RecalculatePosition();

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionViewMatrix;

	/* vector in world space that points to camera position */
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 3.0f };
	glm::vec3 m_CameraFront = { 0.0f, 0.0f, -1.0f };
};