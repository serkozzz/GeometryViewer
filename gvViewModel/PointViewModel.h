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
					PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionX"));
					PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionY"));
					PropertyChanged(this, gcnew PropertyChangedEventArgs("PositionZ"));
				}
				else if (arg.propName == IPoint::rotationPropertyName)
				{
					PropertyChanged(this, gcnew PropertyChangedEventArgs("RotationX"));
					PropertyChanged(this, gcnew PropertyChangedEventArgs("RotationY"));
					PropertyChanged(this, gcnew PropertyChangedEventArgs("RotationZ"));
				}
				else if (arg.propName == IPoint::scalePropertyName)
				{
					PropertyChanged(this, gcnew PropertyChangedEventArgs("ScaleX"));
					PropertyChanged(this, gcnew PropertyChangedEventArgs("ScaleY"));
					PropertyChanged(this, gcnew PropertyChangedEventArgs("ScaleZ"));
				}
				else if (arg.propName == IPoint::primitivePropertyName)
				{

				}
			}

#pragma region Position
		public:

			property float PositionX 
			{
				float get() 
				{
					return _modelPoint->getPosition().x;
				}

				void set(float newx) 
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

			property float RotationX
			{
				float get()
				{
					return _modelPoint->getRotation().x;
				}

				void set(float newX)
				{
					glm::vec3 rot = _modelPoint->getRotation();
					rot.x = newX;	
					_modelPoint->trySetRotation(rot);
				}
			}

			property float RotationY
			{
				float get()
				{
					return _modelPoint->getRotation().y;
				}

				void set(float newY)
				{
					glm::vec3 rot = _modelPoint->getRotation();
					rot.y = newY;	
					_modelPoint->trySetRotation(rot);
				}
			}

			property float RotationZ
			{
				float get()
				{
					return _modelPoint->getRotation().z;
				}

				void set(float newZ)
				{
					glm::vec3 rot = _modelPoint->getRotation();
					rot.z = newZ;	
					_modelPoint->trySetRotation(rot);
				}
			}



			property float ScaleX
			{
				float get()
				{
					return _modelPoint->getScale().x;
				}

				void set(float newX)
				{
					glm::vec3 scale = _modelPoint->getScale();
					scale.x = newX;	
					_modelPoint->trySetScale(scale);
				}
			}

			property float ScaleY
			{
				float get()
				{
					return _modelPoint->getScale().y;
				}

				void set(float newY)
				{
					glm::vec3 scale = _modelPoint->getScale();
					scale.y = newY;	
					_modelPoint->trySetScale(scale);
				}
			}

			property float ScaleZ
			{
				float get()
				{
					return _modelPoint->getScale().z;
				}

				void set(float newZ)
				{
					glm::vec3 scale = _modelPoint->getScale();
					scale.z = newZ;	
					_modelPoint->trySetScale(scale);
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