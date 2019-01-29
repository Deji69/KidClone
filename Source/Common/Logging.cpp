#include <Source/pch.h>
#include <Source/Common.h>
#include <Source/Common/Logging.h>

namespace KidClone {

class DefaultLogger : public ILogger {
public:
	DefaultLogger(std::ostream& out) : m_out(out)
	{ }

	virtual auto write(LogLevel lvl, const string& msg)->void override {
		const char* logLevelStr = nullptr;

		if (lvl == LogLevel::Debug)
			logLevelStr = "DEBUG";
		else if (lvl == LogLevel::Info)
			logLevelStr = "INFO";
		else if (lvl == LogLevel::Warning)
			logLevelStr = "WARNING";
		else if (lvl == LogLevel::Error)
			logLevelStr = "ERROR";

		m_out << "[" << getTimestamp() << "]: ";
		if (logLevelStr) {
			m_out << logLevelStr << ": ";
		}
		m_out << msg;
	}

protected:
	std::ostream& m_out;
};

Logger::Logger(LogLevel level, ILogger& out) : m_level(level), m_logImpl(&out)
{
}
auto Logger::setLogger(ILogger& logger)->void
{
	m_logImpl = &logger;
}

Log::Log(LogLevel level, ILogger* logger) :
	m_level(level),
	m_logger(logger)
{
}

Log::Log(Log&& other) :
	m_level(m_level),
	m_logger(std::move(other.m_logger))
{
	std::swap(m_stream, other.m_stream);
	other.m_logger = nullptr;
}

Log::~Log()
{
	if (m_logger) {
		m_stream << "\n";
		m_logger->write(m_level, m_stream.str());
	}
}

auto Log::operator=(Log&& other)->Log&
{
	m_level = other.m_level;
	std::swap(m_logger, other.m_logger);
	std::swap(m_stream, other.m_stream);
	other.m_logger = nullptr;
	return *this;
}

DefaultLogger defaultLogger(std::cout);
DefaultLogger errorLogger(std::cerr);

Logger& debug()
{
	static Logger logger(LogLevel::Debug, defaultLogger);
	return logger;
}
Logger& info()
{
	static Logger logger(LogLevel::Info, defaultLogger);
	return logger;
}
Logger& warning()
{
	static Logger logger(LogLevel::Warning, defaultLogger);
	return logger;
}
Logger& error()
{
	static Logger logger(LogLevel::Error, errorLogger);
	return logger;
}

} // namespace KidClone
