#include "Logger.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>


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

	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);

	std::stringstream strstrHeader; 
	strstrHeader << std::put_time(std::localtime(&t), "%Y %b %d %H:%M:%S") << ": ";

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
			strstrHeader << "ERROR: ";
			break;
		}
	}
	_writingBehaviour->writeMessage(strstrHeader.str(), message);
}

FileWritingBehavior::FileWritingBehavior(const std::string& fileName) : _fileName(fileName)
{

}

void FileWritingBehavior::writeMessage(const std::string& header, const std::string& message)
{
	std::ofstream stream(_fileName, std::ofstream::app);
	std::string resultMessage = header + message;
	stream << resultMessage << std::endl;
	//stream.close();
}

void StandardOutStreamWritingBehavior::writeMessage(const std::string& header, const std::string& message)
{
	std::cout << header + message << std::endl;
}