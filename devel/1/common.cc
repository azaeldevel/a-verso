#include "common.hh"


namespace oct::verso::v1
{

    VAO::VAO() : id(0),size(0)
    {
    }
    VAO::~VAO()
    {
        glDeleteVertexArrays(size, &id);
    }

    void VAO::generate(int n)
    {
        size = n;
        glGenVertexArrays(size, &id);
    }
    void VAO::bind()
    {
        glBindVertexArray(id);
    }

    VAO::operator GLuint()
    {
        return id;
    }
}
