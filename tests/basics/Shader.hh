
#ifndef OCTETOS_AVERSO_SHADER_HH
#define OCTETOS_AVERSO_SHADER_HH

#include <string>
#include <vector>



#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
//#include <core/3/Exception.hh>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <numbers/0/vector.hh>

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

        //GLuint compile(const std::filesystem::path&,GLenum);
        //GLuint compile(const std::string&,GLenum);
        bool build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);



    private:
        bool is_vextex_file(const std::filesystem::path&)const;
        bool is_fragment_file(const std::filesystem::path&)const;

    private:
        GLuint program;

        GLuint compile(const std::filesystem::path&);
        GLuint compile(const std::filesystem::path&,GLenum);
        GLuint compile(const std::string&,GLenum);
        GLuint compile(const GLchar*,GLenum);
        bool link(GLuint,GLuint);
    };

    class Shader
    {
    public:
        Shader() = default;
        // constructor reads and builds the shader
        Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        operator GLuint()const;

        // use/activate the shader
        void use();
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        template<typename T> void set(const std::string &name, T v1, T v2, T v3) const
        {
            glUniform3f(glGetUniformLocation(program, name.c_str()), v1,v2,v3);
        }
        void set(const std::string &name,  const glm::mat4& ) const;

    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);

        bool build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        bool build(const std::string& vertexCode, const std::string& fragmentCode);
        bool build(const std::vector<shader>&);

        void clean();

    private:
        // the program ID
        unsigned int program;

    private:
        GLuint compile(const std::filesystem::path&,GLenum);
        bool link(GLuint,GLuint);

    };


}

#endif // OCTETOS_AVERSO_SHADER_HH
