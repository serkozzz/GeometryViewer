#pragma once


#include <msclr\marshal_cppstd.h>

#include "IPoint.h"
#include "CLIHelper.h"


using namespace System::ComponentModel;
using namespace msclr::interop;
//using namespace System;
//using namespace System::Collections::Generic;

//using namespace System::Drawing;
//using namespace System::Runtime::CompilerServices;
//using namespace System::Windows::Forms;

namespace gv
{
	namespace View
	{

		public ref class PointViewModel : INotifyPropertyChanged
		{
			int subscriptionId;
			const IPoint* _modelPoint;

			delegate void propChanged(PointPropChangedArgs args);
			propChanged^ _propChangedDel;


		public:

			PointViewModel(const gv::IPoint* modelPoint) : _modelPoint(modelPoint)
			{			
				glm::vec3 p =  _modelPoint->getPosition();
				_propChangedDel =  gcnew propChanged(this, &PointViewModel::modelPointPropertyChangedEvent);
				subscriptionId = 
					(CLIHelper::SubscribeDelegateToUnmanagedEvent(_propChangedDel, _modelPoint->propertyChanged));
			}

			~PointViewModel()
			{
				_modelPoint->propertyChanged -= subscriptionId;
			}

			const IPoint* getModelPoint()
			{
				return _modelPoint;
			}

		private:

			void modelPointPropertyChangedEvent(PointPropChangedArgs arg)
			{
				if (arg.propName ==	IPoint::namePropertyName)
				{
					PropertyChanged(this, gcnew PropertyChangedEventArgs("Name"));
				}
				else if (arg.propName == IPoint::positionPropertyName)
				{
					//PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionX"));
					//PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionY"));
					//PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionZ"));
				}
				else if (arg.propName == IPoint::primitivePropertyName)
				{

				}
			}

		public:

			int _a;
			property int A
			{
				int get() 
				{
					return _a;
				}

				void set( int newx ) 
				{
					_a = newx;
					PropertyChanged(this, gcnew PropertyChangedEventArgs("A"));
				}
			} 

			int _b;
			property int B
			{
				int get() 
				{
					return _b;
				}

				void set( int newx ) 
				{
					_b = newx;
					PropertyChanged(this, gcnew PropertyChangedEventArgs("B"));
				}
			} 

#pragma region Position
		public:

			property int PositionX 
			{
				int get() 
				{
					return _modelPoint->getPosition().x;
				}

				void set(int newx) 
				{
					glm::vec3 pos = _modelPoint->getPosition();
					pos.x = newx;	
					_modelPoint->trySetPosition(pos);
				}
			} 

			property float PositionY
			{
				float get() 
				{
					return _modelPoint->getPosition().y;
				}

				void set(float newy) 
				{
					glm::vec3 pos = _modelPoint->getPosition();
					pos.y = newy;	
					_modelPoint->trySetPosition(pos);
				}
			} 

			property float PositionZ
			{
				float get() 
				{
					return _modelPoint->getPosition().z;
				}

				void set(float newz) 
				{
					glm::vec3 pos = _modelPoint->getPosition();
					pos.z = newz;	
					_modelPoint->trySetPosition(pos);
				}
			} 



#pragma endregion Position

		public:

			property System::String^ Name 
			{
				System::String^ get() 
				{
					System::String^ name = gcnew System::String(_modelPoint->getName().c_str());
					return name;
				}

				void set(System::String^ newName) 
				{
					std::string name = marshal_as<std::string>(newName);
					_modelPoint->trySetName(name);
				}
			} 



		public:
			virtual event PropertyChangedEventHandler^ PropertyChanged;
		};
	}
}