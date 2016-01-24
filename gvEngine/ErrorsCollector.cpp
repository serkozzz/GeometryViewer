#include <algorithm>

#include "ErrorsCollector.h"


using namespace gv::Engine;

ErrorsCollector* ErrorsCollector::_errorsCollectorInstance = nullptr;

ErrorsCollector::ErrorsCollector() : _state(NO_ERROR)
{
}

ErrorsCollector* ErrorsCollector::sharedErrorsCollector()
{
	if (_errorsCollectorInstance == nullptr)
		_errorsCollectorInstance = new ErrorsCollector();
	return _errorsCollectorInstance;
}


ErrorsCollector::State ErrorsCollector::getState()
{
	return _state;
}

void ErrorsCollector::resetState()
{
	std::lock_guard<std::mutex> lock(_mutex);
	_state = ErrorsCollector::NO_ERROR;
}



std::list<std::string> ErrorsCollector::getAllErrors() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return std::list<std::string>(_errors.begin(), _errors.end());
}


std::string ErrorsCollector::getLastError() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_errors.empty())
		return "";
	return _errors.back();
}


std::list<std::string> ErrorsCollector::getLastErrors(int number) const
{
	std::lock_guard<std::mutex> lock(_mutex);
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
	std::lock_guard<std::mutex> lock(_mutex);
	_state = ErrorsCollector::HAS_ERROR;
	_errors.push_back(error);
}