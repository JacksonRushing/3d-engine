#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
class Transform
{
public:
	Transform(const glm::vec3& _pos = glm::vec3(), const glm::vec3& _rot = glm::vec3(), const glm::vec3& _scale = glm::vec3(1.0, 1.0, 1.0)) : 
		pos(_pos),
		rot(_rot),
		scale(_scale)
		{}

	inline glm::mat4 getModel() const
	{
		glm::mat4 posMatrix = glm::translate(pos);
		glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0, 0, 1));
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix; 	// X times Y times Z
		glm::mat4 scaleMatrix = glm::scale(scale);
		
		return posMatrix * rotMatrix * scaleMatrix;

	}

	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec3* getRot() { return &rot; }
	inline glm::vec3*	getScale() { return &scale; }

	inline void setPos(glm::vec3& _pos) { pos = _pos; }
	inline void setRot(glm::vec3& _rot) { rot = _rot; }
	inline void setScale(glm::vec3& _scale) { scale = _scale; }

protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};