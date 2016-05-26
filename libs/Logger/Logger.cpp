#include "Logger.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>


using namespace sk;

//#define DEBUG_LOGGER;


Logger* Logger::_loggerInstance = nullptr;

Logger::Logger(std::shared_ptr<IOutputDeviceDriver> behavior) : _outputDriver(behavior)
{
}

Logger* Logger::sharedLogger()
{
	if (_loggerInstance == nullptr)
	{
		_loggerInstance = new Logger(std::shared_ptr<IOutputDeviceDriver>(new StandardOutStreamDriver()));
	}
	return _loggerInstance;
}


void Logger::setOutputDriver(std::shared_ptr<IOutputDeviceDriver> outputDriver)
{
	_outputDriver = outputDriver;
}


void Logger::writeMessage(const std::string& message, 
						  Logger::MessageType messageType /*= Logger::MessageType::Special*/)
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
	_outputDriver->writeMessage(strstrHeader.str(), message);
}

void Logger::clear()
{
	_outputDriver->clearScreen();
}

OutputToFileDriver::OutputToFileDriver(const std::string& fileName) : _fileName(fileName)
{

}

void OutputToFileDriver::writeMessage(const std::string& header, const std::string& message)
{
	std::ofstream stream(_fileName, std::ofstream::app);
	std::string resultMessage = header + message;
	stream << resultMessage << std::endl;
	//stream.close();
}

void OutputToFileDriver::clearScreen()
{
	std::ofstream stream(_fileName, std::ofstream::trunc);
}


void StandardOutStreamDriver::writeMessage(const std::string& header, const std::string& message)
{
	std::cout << header + message << std::endl;
}


void StandardOutStreamDriver::clearScreen()
{

}