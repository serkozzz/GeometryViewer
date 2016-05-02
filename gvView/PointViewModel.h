#pragma once

#include "IPoint.h"

using namespace System::ComponentModel;
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



			//private IPoint* _modelPoint;

			//property float PositionX 
			//{
			//	float get() 
			//	{
			//		return _modelPoint->getPosition().x;
			//	}

			//	void set( float newx ) 
			//	{
			//		glm::vec3 pos = _modelPoint->getPosition();
			//		pos.x = newx;	
			//		_modelPoint->trySetPosition(pos);
			//	}
			//} 

		public:
			virtual event PropertyChangedEventHandler^ PropertyChanged;
		};
	}
}