#include "scenary.hpp"

namespace oct::verso::v1
{
	IScenary::IScenary() : status(Status::stop)
	{
	}
	IScenary::IScenary(Status r) : status(r)
	{
	}

	void IScenary::run()
	{
		initialize();
		loop();
	}
}