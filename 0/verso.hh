
#ifndef OCTETOS_AVERSO_VERSO_HH
#define OCTETOS_AVERSO_VERSO_HH


namespace oct::verso::v0
{
    class scenary
    {
    private:

    protected:
        bool running;

    protected:

    public:
        virtual void render() = 0;
        virtual void clean() = 0;
        virtual bool initialize() = 0;
        void handle();
        void update();

        bool is_running();
    };

    class verso : public scenary
    {
    public:

    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
