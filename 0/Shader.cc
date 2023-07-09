
#include "Shader.hh"

namespace oct::verso::v0
{

#ifdef OCTETOS_AVERSO_TTD

#endif // OCTETOS_AVERSO_TTD

Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    build(vertexPath,fragmentPath);
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
		std::cout << "Error en compilacion de shader\n";
	}

	return shader_id;
}

void Shader::build(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    program = glCreateProgram();
	glAttachShader(program, compile(vertexPath,GL_VERTEX_SHADER));
	glAttachShader(program, compile(fragmentPath,GL_FRAGMENT_SHADER));
	glLinkProgram(program);

    GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
    {
		/*std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);*/
		std::cout << "Error en contruccion de shader\n";
	}
}

}
