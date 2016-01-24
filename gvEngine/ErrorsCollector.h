#pragma once

#include <mutex>

#include "dllexport.h"
#include "IErrorsCollector.h"

namespace gv
{
	namespace Engine
	{
#ifdef UNIT_TESTS_BUILD
		class GVAPI ErrorsCollector : public IErrorsCollector
#else
		class ErrorsCollector : public IErrorsCollector
#endif
		{
			State _state;
			std::list<std::string> _errors;
			mutable std::mutex _mutex;

			static ErrorsCollector* _errorsCollectorInstance;
			ErrorsCollector();
		public:
			virtual State getState();

			virtual void resetState();

			virtual std::list<std::string> getAllErrors() const;

			virtual std::string getLastError() const;

			/// if errors number is less then number that specified in args
			/// method returns all errors
			virtual std::list<std::string> getLastErrors(int number) const;

			void addError(const std::string error);

			static ErrorsCollector* sharedErrorsCollector();
		};
	}
}