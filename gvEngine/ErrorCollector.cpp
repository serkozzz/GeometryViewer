#include "ErrorCollector.h"


using namespace gv::Engine;



const std::list<std::string>& ErrorCollector::getAllErrors() const
{
	return _errors;
}


std::string ErrorCollector::getLastError() const
{
	if (_errors.empty())
		return "";
	_errors.back();
}


std::list<std::string> ErrorCollector::getLastErrors(int count) const
{
	_errors.
}

void ErrorCollector::addError(const std::string error)
{
	_errors.push_back(error);
}