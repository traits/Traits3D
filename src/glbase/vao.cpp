#include "glb/vao.h"

namespace glb
{

VAO::VAO()
{
    id_ = 0;
    glGenVertexArrays(1, &id_);
}

VAO::~VAO()
{
    //if (GL_TRUE == glIsVertexArray(id_))
    //  glDeleteVertexArrays(1, &id_);
}

void VAO::bind()
{
    GLuint val;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *)(&val));

    if (val != id_)
        glBindVertexArray(id_);
}

void VAO::unbind()
{
    GLuint val;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *)(&val));

    if (val == id_)
        glBindVertexArray(0);
}

} // ns
