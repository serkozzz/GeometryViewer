#pragma once

#include <string>
#include <list>

namespace gv
{
	namespace Engine
	{
		class IErrorsCollector
		{
		public:
			virtual const std::list<std::string>& getAllErrors() const = 0;
			virtual std::string getLastError() const = 0;
			virtual std::list<std::string> getLastErrors(int count) const = 0;
		};
	}
}