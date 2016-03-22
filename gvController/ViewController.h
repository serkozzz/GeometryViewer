#pragma once

#include "../gvView/IView.h"
#include "../gvModel/Model.h"

namespace gv
{
	namespace Controller
	{
		class ViewController
		{
		private:
			View::IView* _view;
			Model::Model* _model;
			Model::PlanManager& _planManager;

			void addPointClick(const std::shared_ptr<IPoint>& p);
			void removePointClick(const std::shared_ptr<IPoint>& p);
			void changePointSizeClick(int newSize);
			void loadPlanClick(const std::string&);
			void savePlanClick(const std::string&);


			int addPointClickSubscription;
			int removePointClickSubscription;
			int changePointSizeSubscription;
			int loadPlanClickSubscription;
			int savePlanClickSubscription;

			void pointAdded(const std::shared_ptr<IPoint>& p);
			void pointRemoved(const std::shared_ptr<IPoint>& p);

			void cameraPropertyChanged(gv::Model::CameraPropChangedArgs args);

			int pointAddedSubscription;
			int pointRemovedSubscription;

		public:
			ViewController(View::IView* view, Model::Model* model);
			~ViewController();
		};
	}
}