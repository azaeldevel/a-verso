
#include <vector>
#include "Shader.hh"

namespace oct::verso::v0
{

#ifdef OCTETOS_AVERSO_TTD

#endif // OCTETOS_AVERSO_TTD

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
    return ID;
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
    ID = glCreateShader(type);
	glShaderSource(ID, 1, &source_str , NULL);
	glCompileShader(ID);

	GLint isCompiled = 0;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(ID, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(ID);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        std::cout << (const char*)&infoLog[0] << "\n";
        return 0;
    }

    return ID;
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






Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    build(vertexPath,fragmentPath);
}
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    build(vertexPath,fragmentPath);
}
Shader::~Shader()
{
    if(program)
    {
        glDeleteProgram(program);
        program = 0;
    }
}

void Shader::clean()
{
    if(program)
    {
        glDeleteProgram(program);
        program = 0;
    }
}

Shader::operator GLuint()const
{
    return program;
}

GLuint Shader::compile(const std::filesystem::path& path,GLenum type)
{
    GLuint shader_id = glCreateShader(type);
    std::string shader_code;
	std::ifstream shader_stream(path, std::ios::in);
	if(shader_stream.is_open())
    {
		std::stringstream sstr;
		sstr << shader_stream.rdbuf();
		shader_code = sstr.str();
		shader_stream.close();
	}
	else
    {
        return 0;
    }

	char const * source_str = shader_code.c_str();
	glShaderSource(shader_id, 1, &source_str , NULL);
	glCompileShader(shader_id);
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
    {
		/*std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(shader_id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);*/
		std::cout << "Error en compilacion de\n";
	}

	return shader_id;
}

bool Shader::build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    shader vertex(vertexPath,GL_VERTEX_SHADER),fragment(fragmentPath,GL_FRAGMENT_SHADER);

	return link(vertex,fragment);
}
bool Shader::build(const std::string& vertexCode, const std::string& fragmentCode)
{
    shader vertex(vertexCode,GL_VERTEX_SHADER),fragment(fragmentCode,GL_FRAGMENT_SHADER);

	return link(vertex,fragment);
}
void Shader::use()
{
    glUseProgram(program);
}
bool Shader::link(GLuint vertex,GLuint fragment)
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


void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
void Shader::set(const std::string &name,  const glm::mat4 &m) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &m[0][0]);
}

    // ------------------------------------------------------------------------
    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
    }

}
