
#ifndef OCTETOS_AVERSO_VERSO_HH
#define OCTETOS_AVERSO_VERSO_HH


namespace oct::verso::v0
{
    class scenary
    {
    private:

    protected:

    public:
        virtual void render() = 0;
        virtual void clean() = 0;
        virtual bool active() = 0;
        //virtual void handle() = 0;
        void update();

        //bool is_running();
    };

    class verso : public scenary
    {
    public:

    protected:
        bool running;

    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
