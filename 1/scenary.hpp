
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
		Status status;

		IScenary();
		IScenary(Status);
		virtual bool initialize() = 0;
		virtual void run();
		virtual void loop() = 0;
	};

}

#endif

