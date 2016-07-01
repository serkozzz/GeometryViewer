#include <msclr\marshal_cppstd.h>

#include "CLIHelper.h"
#include "PointsViewModel.h"


BindingList<PointViewModel^>^ PointsViewModel::GetPoints()
{
	return _pointsVM;
}

