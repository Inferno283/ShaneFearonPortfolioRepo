#ifndef  CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:

	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, (m_position + m_forward), m_up);
	}

	inline glm::mat4 GetViewProjectionSkybox() const
	{
		return m_perspective * glm::mat4(glm::mat3(glm::lookAt(this->m_position, (this->m_position + this->m_forward), this->m_up)));
	}

	inline glm::mat4 GetViewMatrixSkybox() const
	{
		return glm::mat4(glm::mat3(glm::lookAt(this->m_position, (this->m_position + this->m_forward), this->m_up)));
	}

	inline glm::mat4 GetViewMatrix() const
	{
		return glm::mat4(glm::lookAt(this->m_position, (this->m_position + this->m_forward), this->m_up));
	}
	

	inline void SetLookAt(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
	{
		m_position = position;
		m_forward = forward;
		m_up = up;
		glm::lookAt(this->m_position, (this->m_position + this->m_forward), this->m_up);
	}

	inline glm::mat4 GetProjection() const
	{
		return m_perspective;
	}

	inline glm::vec3 GetPos() const
	{
		return m_position;
	}
	inline void SetForward(glm::vec3 setter)
	{
		m_forward = setter;
	}


protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::mat4 viewSkybox;
	
};

#endif // CAMERA_H_INCLUDED

