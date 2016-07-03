#pragma once

#include "../gvModel/PlanElement.h"

namespace gv
{

	namespace ViewModel
	{

		public ref class PlanElementViewModel: System::ComponentModel::INotifyPropertyChanged
		{
			int subscriptionId;
			const Model::PlanElement* _planElement;

			delegate void propChanged(Model::PlanElementPropChangedArgs args);
			propChanged^ _propChangedDel;
		
			void planElementPropertyChangedEvent(Model::PlanElementPropChangedArgs arg);
		
		
		public:

			PlanElementViewModel(const Model::PlanElement* planElement);
			~PlanElementViewModel();


			const Model::PlanElement* getModelPlanElementPtr();

#pragma region Transform

			property float PositionX 
			{
				float get();
				void set(float newx);
			} 

			property float PositionY
			{
				float get();
				void set(float newy);
			} 

			property float PositionZ
			{
				float get();
				void set(float newz);
			} 

			property float RotationX
			{
				float get();
				void set(float newX);
			}

			property float RotationY
			{
				float get();
				void set(float newY);
			}

			property float RotationZ
			{
				float get();
				void set(float newZ);
			}

			property float ScaleX
			{
				float get();
				void set(float newX);
			}

			property float ScaleY
			{
				float get();
				void set(float newY);
			}

			property float ScaleZ
			{
				float get();
				void set(float newZ);
			}

#pragma endregion Transform

			property System::String^ Name 
			{
				System::String^ get();
				void set(System::String^ newName);
			} 

			virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;
		};
	}
}