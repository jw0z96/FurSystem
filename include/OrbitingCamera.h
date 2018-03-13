#ifndef OrbitingCamera_H_
#define OrbitingCamera_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrbitingCamera
{
	public :
		//----------------------------------------------------------------------------------------------------------------------
		OrbitingCamera() = default;
		//----------------------------------------------------------------------------------------------------------------------
		OrbitingCamera(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up = glm::vec3(0.0, 1.0, 0.0));
		//----------------------------------------------------------------------------------------------------------------------
		void set(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up = glm::vec3(0.0, 1.0, 0.0)) noexcept;
		//----------------------------------------------------------------------------------------------------------------------
		void setProjection(float _fov, float _aspect, float _near, float _far) noexcept;
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::mat4 getView() const noexcept {return m_view;};
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::mat4 getProjection() const noexcept {return m_projection;};
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::mat4 getVP() const noexcept {return m_projection * m_view;};
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec3 getEye() const noexcept {return m_eye;};
		//----------------------------------------------------------------------------------------------------------------------
		void updateCameraVectors() noexcept;
		//----------------------------------------------------------------------------------------------------------------------
		void move(float _x, float _y, float _deltaTime);
		//----------------------------------------------------------------------------------------------------------------------
		void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) noexcept;
		//----------------------------------------------------------------------------------------------------------------------
		void processMouseScroll(float _yoffset) noexcept;
		//----------------------------------------------------------------------------------------------------------------------
		void resetPos() noexcept;

	private :
		//----------------------------------------------------------------------------------------------------------------------
		glm::mat4 m_view;
		//----------------------------------------------------------------------------------------------------------------------
		glm::mat4 m_projection;
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 m_eye={2,2,2};
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 m_look={0,0,0};
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 m_worldUp={0,1,0};
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 m_front;
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 m_up;
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 m_right;
		//----------------------------------------------------------------------------------------------------------------------
		float m_yaw=-90.0f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_pitch=0.0f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_speed=2.5f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_sensitivity=0.01f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_zoom=45.0f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_near=0.1f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_far=100.0f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_aspect=1.2f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_theta=0.0f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_phi=0.0f;
		//----------------------------------------------------------------------------------------------------------------------
		float m_radius=5.0f;
		//----------------------------------------------------------------------------------------------------------------------
		void calculateOrbitPos() noexcept;
};

#endif // OrbitingCamera_H_
