#pragma once
#include <Source/Common.h>
#include <string>

namespace KidClone {

using std::string;

class Application;

enum class LogLevel {
	None, Debug, Info, Warning, Error
};

class ILogger {
public:
	virtual ~ILogger() = default;

	virtual auto write(LogLevel level, const string& msg)->void = 0;
};

class Log {
public:
	Log(LogLevel, ILogger*);
	Log(const Log&) = delete;
	Log(Log&&);
	~Log();

	auto operator=(const Log&)->Log& = delete;
	auto operator=(Log&&)->Log&;

	template<typename T>
	auto operator<<(const T& message)->Log&
	{
		m_stream << message;
		return *this;
	}

private:
	ILogger* m_logger;
	LogLevel m_level;
	std::stringstream m_stream;
};

class Logger {
public:
	Logger(LogLevel, ILogger&);

	template<typename T>
	auto operator<<(const T& message)->Log
	{
		Log log(m_level, m_logImpl);
		log << message;
		return log;
	}

	auto setLogger(ILogger&)->void;

private:
	LogLevel m_level;
	ILogger* m_logImpl;
};

extern Logger& debug();
extern Logger& info();
extern Logger& warning();
extern Logger& error();

/*#ifdef KIDCLONE_LOGGING
#  define KIDCLONE_LOG(logger, message) logger(static_cast<std::ostringstream&>(std::ostringstream().flush() << message).str(), __FUNCTION__, __FILE__, __LINE__)
#  ifdef _DEBUG
#    define KIDCLONE_VERBOSE_LOGGING
#    define KIDCLONE_LOGDEBUG(message) KIDCLONE_LOG(KidClone::debug(), message)
#  else
#    define KIDCLONE_LOGDEBUG(message) ((void)0)
#  endif
#  define KIDCLONE_LOGINFO(message) KIDCLONE_LOG(KidClone::info(), message)
#  define KIDCLONE_LOGWARNING(message) KIDCLONE_LOG(KidClone::warning(), message)
#  define KIDCLONE_LOGERROR(message) KIDCLONE_LOG(KidClone::error(), message)
#else
#  define KIDCLONE_LOGDEBUG(message) ((void)0)
#  define KIDCLONE_LOGINFO(message) ((void)0)
#  define KIDCLONE_LOGWARNING(message) ((void)0)
#  define KIDCLONE_LOGERROR(message) ((void)0)
#endif*/

}
