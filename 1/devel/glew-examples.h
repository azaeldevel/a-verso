
#ifndef OCTETOS_VERSO_V3_GLUT_EXAMPLES_H
#define OCTETOS_VERSO_V3_GLUT_EXAMPLES_H

#include "../sdl/scenary.hpp"




//https://cs.lmu.edu/~ray/notes/openglexamples/
namespace oct::verso::v1::devel::glew
{
	struct Scenary : public SDL::OpenGL
	{
		virtual bool initialize();
		virtual void render();
		virtual void loop();
		virtual void clean();
		virtual void run();

	};


}

#endif