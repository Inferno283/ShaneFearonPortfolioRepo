#ifndef  CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	const float MOVEMENT_SPEED = 0.1f;
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
	

	inline void SetLookAt(glm::vec3 p, glm::vec3 forward, glm::vec3 up)
	{
		m_position = p;
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
	void setPos(glm::vec3 newPos)
	{
		m_position = newPos;
	}
	void moveForward()
	{
		glm::normalize(m_forward);
		m_position += MOVEMENT_SPEED*m_forward;
	}
	void moveBackward()
	{
		glm::normalize(m_forward);
		m_position += -MOVEMENT_SPEED*m_forward;
	}
	void strafeLeft()
	{
		glm::normalize(m_forward);
		glm::vec3 strafeDirection = glm::cross(m_forward, m_up);
		m_position += -MOVEMENT_SPEED * strafeDirection;
	}
	void strafeRight()
	{
		glm::normalize(m_forward);
		glm::vec3 strafeDirection = glm::cross(m_forward, m_up);
		m_position += MOVEMENT_SPEED * strafeDirection;
	}
	void moveUpward()
	{
		m_position += MOVEMENT_SPEED*m_up;
	}
	void moveDownward()
	{
		m_position += -MOVEMENT_SPEED*m_up;
	}

	void UpdateCamera()
	{
		glm::lookAt(this->m_position, (this->m_position + this->m_forward), this->m_up);
	}

	void UpdateMouseMovement(const glm::vec2& relativeMouseMovement)
	{
		const float ROTATE_SPEED = 0.01f;
		m_forward = glm::mat3(glm::rotate(-relativeMouseMovement.x*ROTATE_SPEED, m_up)) * m_forward;//x axis rotation
		
		glm::vec3 toRotateAround = glm::cross(m_forward, m_up);

		m_forward = glm::mat3(glm::rotate(relativeMouseMovement.y*ROTATE_SPEED, toRotateAround)) *m_forward;
		
	}
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::mat4 viewSkybox;
	glm::vec2 oldMousePosition;
protected:
private:

	
};

#endif // CAMERA_H_INCLUDED

