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
			enum State
			{
				NO_ERROR,
				HAS_ERROR
			};
			virtual State getState() = 0;
			virtual void resetState() = 0;
			virtual std::list<std::string> getAllErrors() const = 0;
			virtual std::string getLastError() const = 0;
			virtual std::list<std::string> getLastErrors(int count) const = 0;
		};
	}
}