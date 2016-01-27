#include "SceneNode.h"

using namespace gv::Engine;


SceneNode::SceneNode(const std::string& name) : _name(name)
{

}


std::string SceneNode::getName() const
{
	return _name;
}


void SceneNode::setMesh(const std::string& meshName)
{
	throw std::exception("NotImplementedException");
}

glm::mat4 SceneNode::getTransformMatrix() const
{
	return _transformMatrix;
}

void SceneNode::setTransformMatrix(const glm::mat4& transform)
{
	_transformMatrix = transform;
}


glm::vec3 SceneNode::getPosition() const
{
	throw std::exception("NotImplementedException");
}

void SceneNode::setPosition(const glm::vec3& position)
{
	throw std::exception("NotImplementedException");
}

glm::vec3 SceneNode::getScale() const
{
	throw std::exception("NotImplementedException");
}

void SceneNode::setScale(const glm::vec3& scale)
{
	throw std::exception("NotImplementedException");
}
