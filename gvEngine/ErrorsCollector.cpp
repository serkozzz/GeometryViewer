#include <algorithm>

#include "ErrorsCollector.h"


using namespace gv::Engine;

ErrorsCollector* ErrorsCollector::_errorsCollectorInstance = nullptr;


ErrorsCollector::ErrorsCollector()
{
}

ErrorsCollector* ErrorsCollector::sharedErrorsCollector()
{
	if (_errorsCollectorInstance == nullptr)
		_errorsCollectorInstance = new ErrorsCollector();
	return _errorsCollectorInstance;
}

const std::list<std::string>& ErrorsCollector::getAllErrors() const
{
	return _errors;
}


std::string ErrorsCollector::getLastError() const
{
	if (_errors.empty())
		return "";
	return _errors.back();
}


std::list<std::string> ErrorsCollector::getLastErrors(int number) const
{
	int resultNumber = (number < (int)_errors.size()) ? number : _errors.size();

	auto result =  std::list<std::string>(resultNumber);	
	std::list<std::string>::const_reverse_iterator sourceIt = _errors.rbegin();
	std::list<std::string>::reverse_iterator resultIt = result.rbegin();
	for(int i = 0; i < resultNumber; i++)
	{
		*resultIt = *sourceIt;
		sourceIt++; resultIt++;
	}
	return result;
}

void ErrorsCollector::addError(const std::string error)
{
	_errors.push_back(error);
}