#include "Camera.h"
#include "Utils.h"


Camera::Camera(
	const glm::vec3& lookFrom, const glm::vec3& lookAt,
	int width, int height, float fov, float aperture,
	float focusDistance
)
	: m_Width(width), m_Height(height), Fov(fov), m_Ratio(width / (float)height),
	Direction(lookAt), FocusDistance(focusDistance), m_Aperture(aperture), Position(lookFrom)
{
	Update();
}

void Camera::Update()
{
	float theta = glm::radians(Fov);
	float h = glm::tan(theta / 2.0f);
	float viewportHeight = 2.0f * h;
	float viewportWidth = m_Ratio * viewportHeight;

	m_W = glm::normalize(Position - Direction);
	m_U = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_W));
	m_V = glm::cross(m_W, m_U);

	Position = Position;
	m_Horizontal = FocusDistance * viewportWidth * m_U;
	m_Vertical = FocusDistance * viewportHeight * m_V;
	m_LowerLeftCorner = Position - m_Horizontal / 2.0f - m_Vertical / 2.0f - FocusDistance * m_W;

	m_LensRadius = m_Aperture / 2.0f;
}

Ray Camera::GetScreenRay(float x, float y) const
{
	x /= (float)(m_Width - 1);
	y /= (float)(m_Height - 1);
	glm::vec3 rd = m_LensRadius * randomInUnitDisk();
	glm::vec3 offset = m_U * rd.x + m_V * rd.y;

	return Ray(
		Position + offset,
		m_LowerLeftCorner + x * m_Horizontal + y * m_Vertical - Position - offset
	);
}