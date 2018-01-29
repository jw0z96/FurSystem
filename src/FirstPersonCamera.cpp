#include "FirstPersonCamera.h"
#include <iostream>
#include <cmath>

FirstPersonCamera::FirstPersonCamera(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up) :
	m_eye(_eye),
	m_look(_look),
	m_up(_up)
{
	updateCameraVectors();
}

void FirstPersonCamera::set(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up) noexcept
{
	m_eye = _eye;
	m_look = _look;
	m_up = _up;
	updateCameraVectors();
}
void FirstPersonCamera::setProjection(float _fov, float _aspect, float _near, float _far) noexcept
{
	m_zoom = _fov;
	m_aspect = _aspect;
	m_near = _near;
	m_far = _far;
	m_projection = glm::perspective(_fov,_aspect,_near,_far);
}

void FirstPersonCamera::updateCameraVectors() noexcept
{
	// Calculate the new Front vector
	m_front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
	m_front.y = sinf(glm::radians(m_pitch));
	m_front.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);
	// Also re-calculate the Right and Up vector
	m_right = glm::cross(m_front, m_worldUp);  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = glm::cross(m_right, m_front);
	m_right = glm::normalize(m_right);
	m_front = glm::normalize(m_front);
	m_view = glm::lookAt(m_eye, m_eye + m_front, m_up);

}


void FirstPersonCamera::move(float _x, float _y,float _deltaTime)
{
	float velocity = m_speed * _deltaTime;
	m_eye += m_front * velocity*_x;
	m_eye += m_right * velocity*_y;
	updateCameraVectors();


}

void FirstPersonCamera::processMouseMovement(float _xoffset, float _yoffset, bool _constrainPitch ) noexcept
{
	_xoffset *= m_sensitivity;
	_yoffset *= m_sensitivity;

	m_yaw   += _xoffset;
	m_pitch += _yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (_constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	updateCameraVectors();
}

void FirstPersonCamera::processMouseScroll(float _yoffset) noexcept
{
	std::cout<<"zoom "<<_yoffset<<' '<<m_zoom<<'\n';
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
			m_zoom -= _yoffset;
	if (m_zoom <= 1.0f)
			m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
			m_zoom = 45.0f;
	m_projection = glm::perspective(m_zoom, m_aspect, m_near, m_far);

}
