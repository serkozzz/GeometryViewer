#pragma once

#include "../gvModel/Figure.h"

namespace gv
{
	namespace ViewModel
	{
		public ref class PlanElementNameViewModel
		{
			const Model::PlanElement* _planElement;
		public:
			const Model::PlanElement* getPlanElement()
			{
				return _planElement;
			}

			PlanElementNameViewModel(const Model::PlanElement* planElement) : _planElement(planElement)
			{
			}

			property System::String^ Name 
			{
				System::String^ get()
				{
					System::String^ name = gcnew System::String(_planElement->getName().c_str());
					return name;
				}
				void set(System::String^ newName)
				{
					//std::string name = marshal_as<std::string>(newName);
					//_modelFigure->setName(name);
				}
			} 
		};
	}
}