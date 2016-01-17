#pragma once

#include "ICamera.h"

namespace gv
{
	namespace Model
	{
		class mCamera : public ICamera
		{
			glm::mat4 _transform;
			std::string _name;
		public:
			virtual glm::mat4 getTransform() const;
			virtual void trySetTransform(const glm::mat4& newTransform);

			virtual std::string getName() const;
			virtual void trySetName(const std::string& newName);

			skb::EventHandler<CameraPropChangedArgs> tryPropertyChanged;
		};
	}
}