#pragma once

#include <string>
#include <memory>

namespace sk
{
	class IWritingBehavior;

	class Logger
	{
		std::shared_ptr<IWritingBehavior> _writingBehaviour;
		static Logger* _loggerInstance;
		Logger(std::shared_ptr<IWritingBehavior> behavior);
	public:
		static Logger* sharedLogger();

		enum MessageType
		{
			Debug,
			Special,
			Error
		};

		void setBehavior(std::shared_ptr<IWritingBehavior> newBehavior);

		void writeMessage(const std::string& message, 
			Logger::MessageType messageType = Logger::MessageType::Special);
	};



	class IWritingBehavior
	{
	public:
		void virtual writeMessage(const std::string& header, const std::string& message) = 0;
		virtual ~IWritingBehavior()
		{}
	};



	class FileWritingBehavior : public IWritingBehavior
	{
		std::string _fileName;
	public:
		FileWritingBehavior(const std::string& fileName);
		void virtual writeMessage(const std::string& header, const std::string& message);
	};



	class StandardOutStreamWritingBehavior : public IWritingBehavior
	{
	public:
		void virtual writeMessage(const std::string& header, const std::string& message);
	};

}