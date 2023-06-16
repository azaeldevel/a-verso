
#ifndef OCTETOS_AVERSO_VERSO_HH
#define OCTETOS_AVERSO_VERSO_HH


//#include<SDL.h>

namespace oct::verso::v0
{
    class Verso
    {
    private:

    protected:
        bool running;

    public:
        virtual ~Verso();

        virtual void initialize();
        virtual void handleEvents();
        virtual void update();
        virtual void rendering();
        virtual void clean();

        bool is_running();
    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
