#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

#include <EventHandler.h>

namespace gv
{
	struct Transform;
	namespace Model
	{
		class PlanElement;	
		typedef skb::PropertyChangedArgs<PlanElement> PlanElementPropChangedArgs;
		typedef skb::TryPropertyChangedArgs<PlanElement> PlanElementTryPropChangedArgs;

		class PlanElement
		{
			std::string _name;
			std::shared_ptr<Transform> _transform;

		public:

			static const std::string positionPropertyName;
			static const std::string rotationPropertyName;
			static const std::string scalePropertyName;
			static const std::string namePropertyName;
			static const std::string primitivePropertyName;

			PlanElement();

			glm::vec3 getPosition() const;
			void trySetPosition(const glm::vec3& newPosition) const;
			void setPosition(const glm::vec3& newPosition);

			glm::vec3 getRotationEuler() const;
			void trySetRotationEuler(const glm::vec3& newRotation) const;
			void setRotationEuler(const glm::vec3& newRotation);

			glm::vec3 getScale() const;
			void trySetScale(const glm::vec3& newScale) const;
			void setScale(const glm::vec3& newScale);

			std::string getName() const;
			void trySetName(const std::string& newName) const;
			void setName(const std::string& newName);


			skb::EventHandler<PlanElementPropChangedArgs> propertyChanged;
			mutable	skb::EventHandler<PlanElementTryPropChangedArgs> tryPropertyChanged;


		protected:

			virtual void sendPropertyChanged(const std::string& propName) const;
			virtual void sendTryPropertyChanged(const void* newValue, const std::string& propName) const;
		};
	}
}