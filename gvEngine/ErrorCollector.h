#pragma once

#include "IErrorCollector.h"

namespace gv
{
	namespace Engine
	{
		class ErrorCollector : public IErrorCollector
		{
			std::list<std::string> _errors;
		public:
			virtual const std::list<std::string>& getAllErrors() const;
			virtual std::string getLastError() const;
			virtual std::list<std::string> getLastErrors(int count) const;

			void addError(const std::string error)
		};
	}
}