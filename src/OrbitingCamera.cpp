#include "OrbitingCamera.h"
#include <iostream>
#include <cmath>

OrbitingCamera::OrbitingCamera(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up) :
	m_eye(_eye),
	m_look(_look),
	m_up(_up)
{
	updateCameraVectors();
}

void OrbitingCamera::set(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up) noexcept
{
	m_eye = _eye;
	m_look = _look;
	m_up = _up;

	calculateOrbitPos();
	updateCameraVectors();
}

void OrbitingCamera::setProjection(float _fov, float _aspect, float _near, float _far) noexcept
{
	m_zoom = _fov;
	m_aspect = _aspect;
	m_near = _near;
	m_far = _far;
	m_projection = glm::perspective(_fov,_aspect,_near,_far);
}

void OrbitingCamera::updateCameraVectors() noexcept
{
	m_view = glm::lookAt(m_eye, m_look, m_up);
}

void OrbitingCamera::move(float _x, float _y,float _deltaTime)
{
	float velocity = m_speed * _deltaTime;
	m_look.x += velocity * _x;
	m_look.z += velocity * _y;
	updateCameraVectors();
}

void OrbitingCamera::processMouseMovement(float _xoffset, float _yoffset, bool _constrainPitch ) noexcept
{
	m_theta += m_sensitivity * m_sensitivity * _xoffset;
	m_phi += m_sensitivity * m_sensitivity * _yoffset;

	calculateOrbitPos();
	updateCameraVectors();
}

void OrbitingCamera::processMouseScroll(float _yoffset) noexcept
{
	m_radius += _yoffset;

	calculateOrbitPos();
	updateCameraVectors();
}

void OrbitingCamera::calculateOrbitPos() noexcept
{
	m_eye.x = m_radius * cos(m_phi) * sin(m_theta);
	m_eye.y = m_radius * sin(m_phi) * sin(m_theta);
	m_eye.z = m_radius * cos(m_theta);
}
