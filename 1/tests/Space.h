
#include "../sdl/scenary.hpp"

namespace oct::verso::v1::devel
{
	struct Space : public SDL::Scenary
	{
		virtual bool initialize();
		virtual void render();
		virtual void loop();
	};
}