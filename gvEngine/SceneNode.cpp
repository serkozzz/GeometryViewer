#include "SceneNode.h"

using namespace gv::Engine;


SceneNode::SceneNode(const std::string& name) : _name(name)
{

}

SceneNode::SceneNode(const std::string& name, const std::string& meshName) : _name(name), _meshName(meshName)
{

}


SceneNode::SceneNode(const std::string& name, const std::string& meshName, const glm::mat4& transform) 
	:_name(name), _meshName(meshName), _transformMatrix(transform)
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


const std::string& SceneNode::getMesh()
{
	return _meshName;
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
	_transformMatrix[3] = glm::vec4(position, 1.0f);
}

glm::vec3 SceneNode::getScale() const
{
	throw std::exception("NotImplementedException");
}

void SceneNode::setScale(const glm::vec3& scale)
{
	throw std::exception("NotImplementedException");
}
