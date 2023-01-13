#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <iomanip>

static void print(const glm::mat4& matrix)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (matrix[j][i] == -0)
				std::cout << std::setw(7) << 0 << " ";
			else
				std::cout << std::setw(7) << matrix[j][i] << " ";
		}
		std::cout << "\n";
	}
}

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: m_ProjectionMatrix(glm::ortho(left, right, bottom ,top, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
{
	m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateCameraMatrices()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CameraPosition)
		* glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0.0f, 0.0f, 1.0f));

	m_ViewMatrix = glm::inverse(transform);
	m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
	: m_ProjectionMatrix(glm::perspective(fov, aspectRatio, near, far))
{
	glm::vec3 cameraTarget = { 0.0f, 0.0f, 0.0f };  
	glm::vec3 up = { 0.0f, 1.0f, 0.0f };

	/* lookAt(camera position, target position, up vector) */ 
	/* transpose and negate */
	m_ViewMatrix = glm::lookAt(m_CameraPosition, cameraTarget, up);
	m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PerspectiveCamera::SetProjectionMatrix(float fov, float aspectRatio, float near, float far)
{
	m_ProjectionMatrix = glm::perspective(fov, aspectRatio, near, far);
	m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PerspectiveCamera::RecalculatePosition()
{
	glm::vec3 cameraUp = { 0.0f, 1.0f, 0.0f };

	glm::vec3 target = m_CameraPosition + m_CameraFront;
	m_ViewMatrix = glm::lookAt(m_CameraPosition, target, cameraUp);
	m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}


