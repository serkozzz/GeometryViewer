#include "Logger.h"
#include <iostream>
#include <fstream>

using namespace sk;

//#define DEBUG_LOGGER;


Logger* Logger::_loggerInstance = nullptr;

Logger::Logger(std::shared_ptr<IWritingBehavior> behavior) : _writingBehaviour(behavior)
{
}

Logger* Logger::sharedLogger()
{
	if (_loggerInstance == nullptr)
	{
		_loggerInstance = new Logger(std::shared_ptr<IWritingBehavior>(new StandardOutStreamWritingBehavior()));
	}
	return _loggerInstance;
}


void Logger::setBehavior(std::shared_ptr<IWritingBehavior> newBehavior)
{
	_writingBehaviour = newBehavior;
}


void Logger::writeMessage(const std::string& message, 
						  Logger::MessageType messageType /*= Logger::MessageType::Debug*/)
{
	std::string header;
	switch(messageType)
	{
	case Logger::Debug:
		{
#ifndef DEBUG_LOGGER
			return;
#endif // !DEBUG_LOGGER
			break;
		}
	case Logger::Special:
		{
			break;
		}
	case Logger::Error:
		{
			header = "ERROR: ";
			break;
		}
	}
	_writingBehaviour->writeMessage(header, message);
}

FileWritingBehavior::FileWritingBehavior(const std::string& fileName) : _fileName(fileName)
{

}

void FileWritingBehavior::writeMessage(const std::string& header, const std::string& message)
{
	std::ofstream stream(_fileName);
	stream << header << message << std::endl;
}

void StandardOutStreamWritingBehavior::writeMessage(const std::string& header, const std::string& message)
{
	std::cout << header + message << std::endl;
}