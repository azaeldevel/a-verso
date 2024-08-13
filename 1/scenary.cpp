#include "scenary.hpp"

namespace oct::verso::v1
{
	IScenary::IScenary() : status(Status::stop)
	{
	}
	IScenary::IScenary(Status r) : status(r)
	{
	}


	bool IScenary::initialize()
	{
		return true;
	}

	void IScenary::run()
	{
		status = running;
		initialize();
		loop();
	}
	void IScenary::on_active()
	{
	}
	void IScenary::on_deactive()
	{
	}
}