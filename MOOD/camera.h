#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#define PI 3.1415926535
#define RADTODEG 57.2957795131
#define DEGTORAD 0.01745329251
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
	void zoom(int amnt)
	{
		position.z += amnt;
	}
	void move(glm::vec3 proposedMovement)
	{
		
		glm::vec3 translatedMovement;
		const float facingAngle = this->facing.x * PI / 180;
		translatedMovement = glm::vec3(glm::rotateY(proposedMovement, facingAngle));
		translatedMovement.z *= -1;
		this->position += translatedMovement;
	}
	void rotate(glm::vec2 mouseMovement)
	{
		//converting mousemovement into radians
		int thetaX = mouseMovement.x * 3.1415926535;
		int thetaY = mouseMovement.y * 3.1415926535;
		float xComponent = cos(thetaX);
		float yComponent = sin(thetaX);
		
		double lookingX = atan2(this->forward.x, this->forward.z);
		facing.x += mouseMovement.x / 20;
		facing.y += mouseMovement.y / 20;
		if (facing.x > 180)
		{
			facing.x = -180 - (180 - facing.x);
		}
		else if (facing.x < -180)
		{
			facing.x = 180 + (180 + facing.x);
		}

		facing.y = std::max(-90.0f, std::min(facing.y, 90.0f));
		
		forward = glm::vec3(cos(facing.x * DEGTORAD) * RADTODEG, 
						   -tan(facing.y * DEGTORAD) * RADTODEG, 
							sin(facing.x * DEGTORAD) * RADTODEG);
		//std::cout << "facing.x: " << facing.x << std::endl;
		std::cout.precision(2);
		std::cout  << std::fixed /*<< "x= " << forward.x << " y= " << forward.y << " z= " << forward.z  */<< " facing.x= " << facing.x  << "\t\t" << " facing.y= " << facing.x << std::endl;
		//std::cout << "x = " << xComponent << std::endl << "y = " << yComponent << std::endl;
		//this->forward = glm::vec3(0, yComponent, xComponent);
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

	glm::vec2	facing = glm::vec2(0, 0);

	glm::vec3	position,	//position of the camera
				forward,	//whatever direction you percieve as forward
				up;			//whatever direction you percieve as up

	float	zNear,
			zFar,
			fov;
			

	
};

