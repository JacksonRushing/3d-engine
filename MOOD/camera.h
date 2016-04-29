#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
class Camera
{
public:
	Camera() : perspective(glm::mat4()), position(glm::vec3()), forward(glm::vec3()), up(glm::vec3()), zNear(0.0f), zFar(0.0f)
	{
		
	}
	Camera(const glm::vec3 _pos, float _fov, float _aspect, float _zNear, float _zFar)//field of view, aspect ratio, znear and zfar are the closest distance we can see, and the farthest distance we can see. 
	{
		perspective = glm::perspective(_fov, _aspect, _zNear, _zFar);
		position = _pos;
		zNear = _zNear;
		zFar = _zFar;
		fov = _fov;
		//hardcoded up and forward directions, these can be done non hardcoded, but hardcoded for now
		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);
		
	}
	void setRatio(float ratio)
	{
		perspective = glm::perspective(fov, ratio, zNear, zFar);
	}

	inline glm::mat4 getViewProjection() const
	{
		//camera position, position to look at, where you want to look at (forward direction vector) and what direction is up, multiply perspective by that transformation and return
		return perspective * glm::lookAt(position, position + forward, up);
	}

protected:
private:
	glm::mat4	perspective;

	glm::vec3	position,	//position of the camera
				forward,	//whatever direction you percieve as forward
				up;			//whatever direction you percieve as up

	float	zNear,
			zFar,
			fov;
};

