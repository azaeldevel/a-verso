
#ifndef OCTETOS_AVERSO_SHADER_HH
#define OCTETOS_AVERSO_SHADER_HH

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>


#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

namespace oct::verso::v1
{
    //namespace core_here = oct::core::v3;

    class shader
    {
    public:
        shader() = default;
        shader(const std::filesystem::path& path);
        shader(const std::filesystem::path& path,GLenum);
        shader(const std::string& code,GLenum);
        ~shader();

        operator GLuint()const;
        bool build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    private:
        bool is_vextex_file(const std::filesystem::path&)const;
        bool is_fragment_file(const std::filesystem::path&)const;
        GLuint compile(const std::filesystem::path&);
        GLuint compile(const std::filesystem::path&,GLenum);
        GLuint compile(const std::string&,GLenum);
        GLuint compile(const GLchar*,GLenum);
        bool link(GLuint,GLuint);

    private:
        GLuint program;

    };
}

#endif // OCTETOS_AVERSO_SHADER_HH
