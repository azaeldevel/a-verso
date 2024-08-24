
#ifndef OCTETOS_VERSO_V3_SCENARY_HPP
#define OCTETOS_VERSO_V3_SCENARY_HPP

#define OCTETOS_VERSO_V3_SCENARY_HPP_ONCE

#include "common.hh"
#include "../../../numbers/0/vector.hh"

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
        constexpr IScenary(const std::initializer_list<real>& l)
        {
            if(l.size() != 3)
            {
                throw core::exception("Cantidad de datos incorrecta.");
                return;
            }
            const real* c = std::data(l);
            for(size_t i = 0; i < l.size(); i++)
            {
                position[i] = c[i];
            }
            position.print(std::cout);
        }
        constexpr IScenary(const numbers::vector<real>& p) : position(p)
        {
        }


		virtual bool initialize();

		virtual void run();
		virtual void loop();

		virtual void on_active();
		virtual void on_deactive();

		Status status;
        numbers::vector<real,3> position;
	};

}

#endif

