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

    void VAO::generate(GLsizei n)
    {
        if(size) glDeleteVertexArrays(size, &id);
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



    BO::BO() : id(0),size(0)
    {
    }
    BO::~BO()
    {
        glDeleteBuffers(size, &id);
    }

    void BO::generate(int n)
    {
        if(size) glDeleteBuffers(size, &id);
        size = n;
        glGenBuffers(size, &id);
    }
    void BO::bind(GLenum target)
    {
        glBindBuffer(target,id);
    }

    BO::operator GLuint()
    {
        return id;
    }
}
