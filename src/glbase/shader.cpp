#include <vector>
#include <fstream>
#include <string>
#include "glb/shader.h"

namespace glb
{

Shader::Shader()
    : initialized_(false), program_id_(0)
{
}

bool Shader::load(std::string &result, std::string const &path)
{
    result.clear();
    std::ifstream shader_stream(path, std::ios::in);

    if (shader_stream.is_open())
    {
        std::string Line = "";

        while (std::getline(shader_stream, Line))
            result += "\n" + Line;

        shader_stream.close();
        return true;
    }

    return false;
}

bool Shader::compile(GLuint shader_id, std::vector<std::string> const &shader_code)
{
    if (0 == shader_id || shader_code.empty())
        return false;

    GLint result = GL_FALSE;
    // Compile shader
    std::vector<const char *> pptr(shader_code.size());

    for (auto i = 0; i != shader_code.size(); ++i)
        pptr[i] = shader_code[i].c_str();

    glShaderSource(shader_id, static_cast<GLsizei>(pptr.size()), &pptr[0], NULL);
    //char const* text = shader_code.c_str();
    //glShaderSource(shader_id, 1, &text, NULL);
    glCompileShader(shader_id);
    // Check shader
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if (GL_FALSE == result)
    {
        int infolog_size;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infolog_size);

        if (infolog_size > 0)
        {
            std::vector<char> shader_error(infolog_size + 1);
            glGetShaderInfoLog(shader_id, infolog_size, NULL, &shader_error[0]);
            last_error_info_ = std::string(shader_error.begin(), shader_error.end());
            std::cerr << __FUNCTION__ << ": " << last_error_info_ << std::endl;
        }
    }

    return (GL_TRUE == result) ? true : false;
}

bool Shader::compile(GLuint shader_id, std::string const &shader_code)
{
    return compile(shader_id, std::vector<std::string>(1, shader_code));
}

bool Shader::link(GLuint vertex_shader_id, GLuint fragment_shader_id, GLuint geometry_shader_id /*= 0*/)
{
    GLint result = GL_FALSE;
    // Link the program
    //printf("Linking program\n");
    program_id_ = glCreateProgram();
    glAttachShader(program_id_, vertex_shader_id);
    glAttachShader(program_id_, fragment_shader_id);

    if (geometry_shader_id > 0)
        glAttachShader(program_id_, geometry_shader_id);

    glLinkProgram(program_id_);
    glDetachShader(program_id_, vertex_shader_id);
    glDetachShader(program_id_, fragment_shader_id);

    if (geometry_shader_id > 0)
        glDetachShader(program_id_, geometry_shader_id);

    // Check the program
    glGetProgramiv(program_id_, GL_LINK_STATUS, &result);

    if (GL_FALSE == result)
    {
        int infolog_size;
        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &infolog_size);

        if (infolog_size > 0)
        {
            std::vector<char> program_error(infolog_size + 1);
            glGetProgramInfoLog(program_id_, infolog_size, NULL, &program_error[0]);
            last_error_info_ = std::string(program_error.begin(), program_error.end());
            std::cerr << __FUNCTION__ << ": " << last_error_info_ << std::endl;
        }
    }

    return (result == GL_TRUE) ? true : false;
}

bool Shader::create(
    std::vector<std::string> const &vertex_code,
    std::vector<std::string> const &fragment_code,
    std::vector<std::string> const &geometry_code /* = std::vector<std::string>()*/
)
{
    initialized_ = false;
    GLuint vid = glCreateShader(GL_VERTEX_SHADER);
    GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint gid = 0;

    if (!geometry_code.empty())
        gid = glCreateShader(GL_GEOMETRY_SHADER);

    if (!compile(vid, vertex_code)
        || !compile(fid, fragment_code)
        || (gid && !compile(gid, geometry_code))
        || !link(vid, fid, gid)
       )
    {
        glDeleteShader(vid);
        glDeleteShader(fid);
        glDeleteShader(gid); // ignores zero
        return false;
    }

    glDeleteShader(vid);
    glDeleteShader(fid);
    glDeleteShader(gid);
    initialized_ = true;
    return true;
}

bool Shader::create(
    std::string const &vertex_code,
    std::string const &fragment_code,
    std::string const &geometry_code /* ="" */
)
{
    return create(
               std::vector<std::string>(1, vertex_code),
               std::vector<std::string>(1, fragment_code),
               (geometry_code.empty())
               ? std::vector<std::string>()
               : std::vector<std::string>(1, geometry_code)
           );
}

//bool Shader::create()
//{
//  const char* vsrc =
//    "attribute highp vec4 vertex;\n"
//    "attribute mediump vec4 texCoord;\n"
//    "varying mediump vec4 texc;\n"
//    "uniform mediump mat4 matrix;\n"
//    "void main(void)\n"
//    "{\n"
//    "    gl_Position = matrix * vertex;\n"
//    "    texc = texCoord;\n"
//    "}\n";
//
//  const char* fsrc =
//    "uniform sampler2D texture;\n"
//    "varying mediump vec4 texc;\n"
//    "void main(void)\n"
//    "{\n"
//    "    gl_FragColor = texture2D(texture, texc.st);\n"
//    "}\n";
//
//  return  create(vsrc, fsrc);
//}

bool Shader::createFromFile(
    std::string const &vertex_file_path,
    std::string const &fragment_file_path,
    std::string const &geometry_file_path /* = ""*/
)
{
    std::string vertex_code;

    if (!load(vertex_code, vertex_file_path))
        return false;

    std::string fragment_code;

    if (!load(fragment_code, fragment_file_path))
        return false;

    std::string geometry_code;

    if (!geometry_file_path.empty() && !load(geometry_code, geometry_file_path))
        return false;

    return create(vertex_code, fragment_code, geometry_code);
}

GLint Shader::getUniform(std::string const &name)
{
    if (name.empty() || !use())
        return -1;

    GLint loc = glGetUniformLocation(program_id_, name.c_str());

    if (GL_NO_ERROR != logGlError())
        return -1;

    return loc;
}

bool Shader::setUniformFloat(float val, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc)
        return false;

    glUniform1f(loc, val);
    return (GL_NO_ERROR == logGlError()) ? true : false;
}


bool Shader::setUniformMatrix(glm::mat3 const &mat, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc)
        return false;

    glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]);
    return (GL_NO_ERROR == logGlError()) ? true : false;
}

bool Shader::setUniformMatrix(glm::mat4 const &mat, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc)
        return false;

    glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    return (GL_NO_ERROR == logGlError()) ? true : false;
}

bool Shader::setUniformVec2(glm::vec2 const &vec, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc)
        return false;

    glUniform2fv(loc, 1, &vec[0]);
    return (GL_NO_ERROR == logGlError()) ? true : false;
}

bool Shader::setUniformVec3(glm::vec3 const &vec, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc)
        return false;

    glUniform3fv(loc, 1, &vec[0]);
    return (GL_NO_ERROR == logGlError()) ? true : false;
}

bool Shader::setUniformVec4(glm::vec4 const &vec, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc)
        return false;

    glUniform4fv(loc, 1, &vec[0]);
    return (GL_NO_ERROR == logGlError()) ? true : false;
}

bool Shader::setUniformArrayVec3(std::vector<glm::vec3> const &vec, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc || vec.empty())
        return false;

    glUniform3fv(loc, static_cast<GLsizei>(sizeof(glm::vec3)*vec.size()), glm::value_ptr(vec[0]));
    return (GL_NO_ERROR == logGlError()) ? true : false;
}

bool Shader::setUniformArrayVec4(std::vector<glm::vec4> const &vec, std::string const &name)
{
    GLint loc = getUniform(name);

    if (-1 == loc || vec.empty())
        return false;

    glUniform4fv(loc, static_cast<GLsizei>(sizeof(glm::vec4)*vec.size()), glm::value_ptr(vec[0]));
    return (GL_NO_ERROR == logGlError()) ? true : false;
}

bool Shader::use()
{
    if (!initialized_)
        return false;

    if (inUse())
        return true;

    glUseProgram(program_id_);

    if (GL_NO_ERROR != logGlError())
        return false;

    return true;
}

bool Shader::inUse() const
{
    if (!initialized_)
        return false;

    GLint currprog;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currprog);

    if (GL_NO_ERROR != logGlError())
        return false;

    return static_cast<GLuint>(currprog) == program_id_;
}

} // ns
