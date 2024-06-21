
#include <vector>
#include "shader.hh"

namespace oct::verso::v1
{

shader::shader(const std::filesystem::path& path)
{
    compile(path);
}
shader::shader(const std::filesystem::path& path,GLenum type)
{
    compile(path,type);
}
shader::shader(const std::string& code,GLenum type)
{
    compile(code,type);
}
shader::~shader()
{

}
shader::operator GLuint()const
{
    return program;
}


GLuint shader::compile(const std::filesystem::path& path)
{
    if(is_vextex_file(path))
    {
        return compile(path,GL_VERTEX_SHADER);
    }
    else if(is_fragment_file(path))
    {
        return compile(path,GL_FRAGMENT_SHADER);
    }
    else
    {
        std::cerr << "Se deconoce el tipo de shader:" << path << "\n";
    }

    return 0;
}
GLuint shader::compile(const std::filesystem::path& path,GLenum type)
{
    std::string shader_code;
	std::ifstream shader_stream(path, std::ios::in);
	if(shader_stream.is_open())
    {
		std::stringstream sstr;
		sstr << shader_stream.rdbuf();
		shader_code = sstr.str();
		shader_stream.close();
        return compile(shader_code,type);
	}
	else
    {
        std::cerr << "Fallo la apertura del archivo:" << path << "\n";
        return 0;
    }
}
GLuint shader::compile(const std::string& shader_code,GLenum type)
{
    const GLchar *source_str = shader_code.c_str();
    return compile(source_str,type);
}
GLuint shader::compile(const GLchar* source_str,GLenum type)
{
    program = glCreateShader(type);
	glShaderSource(program, 1, &source_str , NULL);
	glCompileShader(program);

	GLint isCompiled = 0;
    glGetShaderiv(program, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(program);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        std::cout << (const char*)&infoLog[0] << "\n";
        return 0;
    }

    return program;
}
bool shader::is_vextex_file(const std::filesystem::path& path)const
{
    if(path.extension().string().compare("vs") == 0)
    {
        return true;
    }
    else if(path.extension().string().compare("vertex") == 0)
    {
        return true;
    }

    return false;
}
bool shader::is_fragment_file(const std::filesystem::path& path)const
{
    if(path.extension().string().compare("fs") == 0)
    {
        return true;
    }
    else if(path.extension().string().compare("fragment") == 0)
    {
        return true;
    }

    return false;
}


bool shader::link(GLuint vertex,GLuint fragment)
{
    program = glCreateProgram();
    //glAttachShader(program, compile(vertexPath,GL_VERTEX_SHADER));
	glAttachShader(program, vertex);
	//glAttachShader(program, compile(fragmentPath,GL_FRAGMENT_SHADER));
	glAttachShader(program, fragment);
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        std::cout << "Error en enlazado\n";
        return false;
    }
    glDetachShader(program, vertex);
    glDetachShader(program, fragment);

	return true;
}

bool shader::build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    shader vertex(vertexPath,GL_VERTEX_SHADER),fragment(fragmentPath,GL_FRAGMENT_SHADER);

	return link(vertex,fragment);
}


}
