#pragma once
#include <Source/Common.h>

namespace KidClone {

class NoCopy {
protected:
	NoCopy() = default;
	~NoCopy() = default;

private:
	NoCopy(const NoCopy&) = delete;
	NoCopy& operator=(const NoCopy&) = delete;
};

}
