#pragma once
#include <Source/Common.h>
#include <exception>

namespace KidClone {

class EngineError : public std::exception
{
public:
	EngineError(const char* message) : exception(message)
	{ }
	EngineError(const string& message) : EngineError(message.c_str())
	{ }
};

}
