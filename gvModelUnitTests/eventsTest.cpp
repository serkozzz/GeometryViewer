#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <list>
#include <algorithm>
#include "../gvModel/Point.h"

#include "Call.h"


using namespace gv::Model;

namespace gvModelUnitTests
{		
	TEST_CLASS(eventsTest)
	{
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;
		gv::PrimitiveType _primitive;

		std::string _name;

		std::list<Call> _callList;


		bool checkEvents(std::list<Call>& realCallList, std::list<Call>& requiredCallList)
		{
			if (realCallList.size() != requiredCallList.size())
				return false;

			size_t size = realCallList.size();

			for (auto it = requiredCallList.begin(); it != requiredCallList.end(); it++)
			{
				auto realCallIt = std::find(realCallList.begin(), realCallList.end(), *it);
				if (realCallIt == realCallList.end())
					return false;
				realCallList.erase(realCallIt);
			}
			return true;
		}

		void planElementPropChanged(PlanElementPropChangedArgs& arg)
		{
			_callList.push_back(Call(Methods::planElementPropChangedMethods, arg.propName));
		}


		void pointPropChanged(PointPropChangedArgs& arg)
		{
			_callList.push_back(Call(Methods::pointPropChangedMethods, arg.propName));
		}


		void planElementTryPropChanged(PlanElementTryPropChangedArgs& arg)
		{
			_callList.push_back(Call(Methods::planElementTryPropChangedMethods, arg.propName));
		}


		void pointTryPropChanged(PointTryPropChangedArgs& arg)
		{
			_callList.push_back(Call(Methods::pointTryPropChangedMethods, arg.propName));
		}

	public:

		TEST_METHOD(PointEventsTest)
		{

			_position = glm::vec3(3.2f, 0.5f, 9.1f);
			_rotation = glm::vec3(0.6f, 1.1f, 1.0f);
			_scale = glm::vec3(0.1f, 0.1f, 0.1f);
			_name = "test_point1";
			_primitive = gv::PrimitiveType::cubePrimitiveType;

			Point point1;
			PlanElement* planElement = &point1;
			int planElemPropChangedSubscrId = 
				(planElement->propertyChanged += std::bind(&eventsTest::planElementPropChanged, this, std::placeholders::_1));
			int planElemTryPropChangedSubscrId = 
				(planElement->tryPropertyChanged += std::bind(&eventsTest::planElementTryPropChanged, this, std::placeholders::_1));

			int pointPropChangedSubscrId = 
				(point1.propertyChanged += std::bind(&eventsTest::pointPropChanged, this, std::placeholders::_1));

			int pointTryPropChangedSubscrId = 
				(point1.tryPropertyChanged += std::bind(&eventsTest::pointTryPropChanged, this, std::placeholders::_1));

		
#pragma region TryPropertyChanged
			point1.trySetName(_name);
			std::list<Call> requiredCallList;
			requiredCallList.push_back(Call(Methods::planElementTryPropChangedMethods, Point::namePropertyName));
			requiredCallList.push_back(Call(Methods::pointTryPropChangedMethods, Point::namePropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();

			point1.trySetPosition(_position);
			requiredCallList.push_back(Call(Methods::planElementTryPropChangedMethods, Point::positionPropertyName));
			requiredCallList.push_back(Call(Methods::pointTryPropChangedMethods, Point::positionPropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();

			point1.trySetScale(_scale);
			requiredCallList.push_back(Call(Methods::planElementTryPropChangedMethods, Point::scalePropertyName));
			requiredCallList.push_back(Call(Methods::pointTryPropChangedMethods, Point::scalePropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();


			point1.trySetRotationEuler(_rotation);
			requiredCallList.push_back(Call(Methods::planElementTryPropChangedMethods, Point::rotationPropertyName));
			requiredCallList.push_back(Call(Methods::pointTryPropChangedMethods, Point::rotationPropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();


			point1.trySetPrimitive(_primitive);
			requiredCallList.push_back(Call(Methods::planElementTryPropChangedMethods, Point::primitivePropertyName));
			requiredCallList.push_back(Call(Methods::pointTryPropChangedMethods, Point::primitivePropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();

#pragma endregion TryPropertyChanged

#pragma region PropertyChanged
			point1.setName(_name);
			requiredCallList;
			requiredCallList.push_back(Call(Methods::planElementPropChangedMethods, Point::namePropertyName));
			requiredCallList.push_back(Call(Methods::pointPropChangedMethods, Point::namePropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();

			point1.setPosition(_position);
			requiredCallList.push_back(Call(Methods::planElementPropChangedMethods, Point::positionPropertyName));
			requiredCallList.push_back(Call(Methods::pointPropChangedMethods, Point::positionPropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();

			point1.setScale(_scale);
			requiredCallList.push_back(Call(Methods::planElementPropChangedMethods, Point::scalePropertyName));
			requiredCallList.push_back(Call(Methods::pointPropChangedMethods, Point::scalePropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();


			point1.setRotationEuler(_rotation);
			requiredCallList.push_back(Call(Methods::planElementPropChangedMethods, Point::rotationPropertyName));
			requiredCallList.push_back(Call(Methods::pointPropChangedMethods, Point::rotationPropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();


			point1.setPrimitive(_primitive);
			requiredCallList.push_back(Call(Methods::planElementPropChangedMethods, Point::primitivePropertyName));
			requiredCallList.push_back(Call(Methods::pointPropChangedMethods, Point::primitivePropertyName));
			if (!checkEvents(_callList, requiredCallList))
				Assert::Fail();
			requiredCallList.clear();
			_callList.clear();

#pragma endregion PropertyChanged


			planElement->propertyChanged -= planElemPropChangedSubscrId;
			planElement->tryPropertyChanged -= planElemTryPropChangedSubscrId;

			point1.propertyChanged -= pointPropChangedSubscrId;
			point1.tryPropertyChanged -= pointTryPropChangedSubscrId;
		}

	};
}