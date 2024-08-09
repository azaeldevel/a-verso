
#ifndef OCTETOS_AVERSO_SHADER_HH
#define OCTETOS_AVERSO_SHADER_HH

#include "common.hh"

#include <string>
#include <vector>
#include <filesystem>


#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

namespace oct::verso::v1
{
    //namespace core_here = oct::core::v3;

    /**
    *\brief Represeanta un Shader
    */
    class Shader
    {
    public:
        Shader() = default;
        Shader(const std::filesystem::path& path);
        Shader(const std::filesystem::path& path,GLenum);
        Shader(const std::string& code,GLenum);
        ~Shader();

        operator GLuint()const;

        /**
        *\brief Crea dos shasder a partir de los archivos indicados y los construlle
        */
        bool build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    private:
        bool is_vextex_file(const std::filesystem::path&)const;
        bool is_fragment_file(const std::filesystem::path&)const;
        GLuint compile(const std::filesystem::path&);
        GLuint compile(const std::filesystem::path&,GLenum);
        GLuint compile(const std::string&,GLenum);
        GLuint compile(const GLchar*,GLenum);

        /**
        *\brief Enlaza los dos shader indicado para crea el actual
        */
        bool link(GLuint,GLuint);

    private:
        GLuint program;

    };
}

#endif // OCTETOS_AVERSO_SHADER_HH
