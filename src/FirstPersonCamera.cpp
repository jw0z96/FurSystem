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

	m_eye.x = m_radius*cos(m_phi)*sin(m_theta);
	m_eye.y = m_radius*sin(m_phi)*sin(m_theta);
	m_eye.z = m_radius*cos(m_theta);

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
	m_view = glm::lookAt(m_eye, m_look, m_up);
}

void FirstPersonCamera::move(float _x, float _y,float _deltaTime)
{
	// float velocity = m_speed * _deltaTime;
	// m_eye += m_front * velocity*_x;
	// m_eye += m_right * velocity*_y;
	// updateCameraVectors();
}

void FirstPersonCamera::processMouseMovement(float _xoffset, float _yoffset, bool _constrainPitch ) noexcept
{
	m_theta += m_sensitivity * m_sensitivity * _xoffset;
	m_phi += m_sensitivity * m_sensitivity * _yoffset;

	m_eye.x = m_radius * cos(m_phi) * sin(m_theta);
	m_eye.y = m_radius * sin(m_phi) * sin(m_theta);
	m_eye.z = m_radius * cos(m_theta);

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
