#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
class Camera
{
public:
	Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar)//znear and zfar are the closest distance we can see, and the farthest distance we can see.
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar);
		position = pos;
		//hardcoded up and forward directions, these can be done non hardcoded, but hardcoded for now
		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 getViewProjection() const
	{
		//camera position, position to look at, where you want to look at (forward direction vector) and what direction is up, multiply perspective by that transformation and return
		return perspective * glm::lookAt(position, position + forward, up);
	}

protected:
private:
	glm::mat4 perspective;
	glm::vec3 position;	//position of the camera
	glm::vec3 forward;	//whatever direction you percieve as forward
	glm::vec3 up;		//whatever direction you percieve as up
};

