#include "scenary.hh"

namespace oct::verso::v1
{
	IScenary::IScenary() : status(Status::stop),position{0,0,0}
	{
	}
	IScenary::IScenary(Status r) : status(r),position{0,0,0}
	{
	}


	bool IScenary::initialize()
	{
		return true;
	}
	void IScenary::run()
	{
		status = running;
		this->initialize();
		this->loop();
	}
	void IScenary::loop()
	{
	}
	void IScenary::on_active()
	{
	}
	void IScenary::on_deactive()
	{
	}
}
