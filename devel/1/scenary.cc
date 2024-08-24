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
	void IScenary::clean()
	{
	}
	void IScenary::run()
	{
		status = running;
		this->initialize();
		this->loop();
		this->clean();
	}
	void IScenary::loop()
	{
	    while (status != Status::stop)
        {
            this->handler();
            this->update();
            this->render();
        }
	}
	void IScenary::on_active()
	{
	}
	void IScenary::on_deactive()
	{
	}


	void IScenary::handler()
	{
	}
	void IScenary::update()
	{
	}
	void IScenary::render()
	{
	}
}
