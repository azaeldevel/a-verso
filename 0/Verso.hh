
#ifndef OCTETOS_AVERSO_VERSO_HH
#define OCTETOS_AVERSO_VERSO_HH


namespace oct::verso::v0
{
    class Verso
    {
    private:

    protected:
        bool running;

        void handleEvents();
        void update();

    public:
        virtual ~Verso();

        virtual void render() = 0;
        virtual void clean() = 0;

        bool is_running();
    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
