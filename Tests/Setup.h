#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Source/Common.h>
#include <Source/Common/Logging.h>
#include <Source/Engine/Engine.h>

using namespace KidClone;

class MockEngine : public Engine {
public:
	virtual ~MockEngine() { }
};

class EngineTest : public ::testing::Test {
protected:
	MockEngine m_engine;
	Window m_window;

public:
	EngineTest() {
		m_window.create("Test", VideoMode{640, 480, 32});
	}
	virtual ~EngineTest() { };
};

class TestLogger : public ILogger {
public:
	static std::stringstream testLogStream;

	std::ostream& stream;
	std::string lastLog;
	LogLevel lastLogLevel = LogLevel::None;

	TestLogger() : stream(testLogStream)
	{
	}

	virtual auto write(LogLevel logLevel, const string& msg)->void override
	{
		stream << logLevelToString(logLevel) << ": " << msg << "\n";
		lastLog += msg;
		lastLogLevel = logLevel;
	}

private:
	static constexpr auto logLevelToString(LogLevel lvl)->const char*
	{
		const char* level = "UNKNOWN";
		if (lvl == LogLevel::Debug)
			level = "DEBUG";
		else if (lvl == LogLevel::Info)
			level = "INFO";
		else if (lvl == LogLevel::Warning)
			level = "WARNING";
		else if (lvl == LogLevel::Error)
			level = "ERROR";
		return level;
	}
};

extern TestLogger testLog;
