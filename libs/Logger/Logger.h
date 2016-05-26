#pragma once

#include <string>
#include <memory>

namespace sk
{
	class IOutputDeviceDriver;

	class Logger
	{
		std::shared_ptr<IOutputDeviceDriver> _outputDriver;
		static Logger* _loggerInstance;
		Logger(std::shared_ptr<IOutputDeviceDriver> outputDriver);
	public:
		static Logger* sharedLogger();

		enum MessageType
		{
			Debug,
			Special,
			Error
		};

		void setOutputDriver(std::shared_ptr<IOutputDeviceDriver> outputDriver);

		void writeMessage(const std::string& message, 
			Logger::MessageType messageType = Logger::MessageType::Special);

		void clear();

	};



	class IOutputDeviceDriver
	{
	public:
		void virtual writeMessage(const std::string& header, const std::string& message) = 0;
		void virtual clearScreen() = 0;
		virtual ~IOutputDeviceDriver()
		{}
	};



	class OutputToFileDriver : public IOutputDeviceDriver
	{
		std::string _fileName;
	public:
		OutputToFileDriver(const std::string& fileName);
		void virtual writeMessage(const std::string& header, const std::string& message);
		void virtual clearScreen();	
	};



	class StandardOutStreamDriver : public IOutputDeviceDriver
	{
	public:
		void virtual writeMessage(const std::string& header, const std::string& message);
		void virtual clearScreen();
	};

}