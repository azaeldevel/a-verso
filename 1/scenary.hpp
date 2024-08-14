
#ifndef OCTETOS_VERSO_V3_SCENARY_HPP
#define OCTETOS_VERSO_V3_SCENARY_HPP

#define OCTETOS_VERSO_V3_SCENARY_HPP_ONCE

namespace oct::verso::v1
{
	struct IScenary
	{
		enum Status
		{
			stop,//igual a false
			star,
			running,
		};

		IScenary();
		IScenary(Status);

		virtual bool initialize();

		virtual void run();
		virtual void loop();

		virtual void on_active();
		virtual void on_deactive();

		Status status;

	};

}

#endif

