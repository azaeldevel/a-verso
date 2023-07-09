
#ifndef OCTETOS_AVERSO_SHADER_HH
#define OCTETOS_AVERSO_SHADER_HH

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <core/3/Exception.hh>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;

    class Shader
    {
    public:
        Shader() = default;
        // constructor reads and builds the shader
        Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

        operator GLuint()const;

        // use/activate the shader
        void use();
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

        void build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    private:
        // the program ID
        unsigned int program;

    private:
        GLuint compile(const std::filesystem::path&,GLenum);

    };


}

#endif // OCTETOS_AVERSO_SHADER_HH
