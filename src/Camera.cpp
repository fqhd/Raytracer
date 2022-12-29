#include "Camera.h"
#include "Utils.h"


Camera::Camera(
	const glm::vec3& lookFrom, const glm::vec3& lookAt,
	const glm::vec3& lookUp, int width, int height,
	float fov, float aperture, float focusDistance
)
	: m_Width(width), m_Height(height), m_Fov(fov)
{
	m_Ratio = width / (float)height;
	float theta = glm::radians(m_Fov);
	float h = glm::tan(theta / 2.0f);
	float viewportHeight = 2.0 * h;
	float viewportWidth = m_Ratio * viewportHeight;

	m_W = glm::normalize(lookFrom - lookAt);
	m_U = glm::normalize(glm::cross(lookUp, m_W));
	m_V = glm::cross(m_W, m_U);

	m_Origin = lookFrom;
	m_Horizontal = focusDistance * viewportWidth * m_U;
	m_Vertical = focusDistance * viewportHeight * m_V;
	m_LowerLeftCorner = m_Origin - m_Horizontal / 2.0f - m_Vertical / 2.0f - focusDistance * m_W;

	m_LensRadius = aperture / 2.0f;
}

Ray Camera::GetScreenRay(float x, float y) const
{
	x /= (float)(m_Width - 1);
	y /= (float)(m_Height - 1);
	glm::vec3 rd = m_LensRadius * randomInUnitDisk();
	glm::vec3 offset = m_U * rd.x + m_V * rd.y;

	return Ray(
		m_Origin + offset,
		m_LowerLeftCorner + x * m_Horizontal + y * m_Vertical - m_Origin - offset
	);
}