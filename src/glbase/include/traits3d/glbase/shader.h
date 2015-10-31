#pragma once

#include <map>
#include "traits3d/glbase/glhelper.h"

namespace traits3d
{
namespace gl
{

class Transformation;

//! Shader program, containing various GLSL shaders
class Shader
{
public:
    Shader();

    ////! Create complete shader program with standard shaders
    //bool create();

    //! Create complete shader program from multiple shader source codes
    bool create(
        std::vector<std::string> const &vertex_code,
        std::vector<std::string> const &fragment_code,
        std::vector<std::string> const &geometry_code = std::vector<std::string>()
    );

    //! Create complete shader program from string
    bool create(
        std::string const &vertex_code,
        std::string const &fragment_code,
        std::string const &geometry_code = ""
    );

    //! Create complete shader program from file sources
    bool createFromFile(
        std::string const &vertex_file_path,
        std::string const &fragment_file_path,
        std::string const &geometry_file_path = ""
    );

    //! Shader contains a valid fragment- and vertex-shader
    bool initialized() const
    {
        return initialized_;
    }

    //! For initialized()==true, the function returns a valid shader program id
    GLuint programId() const
    {
        return program_id_;
    }

    //! calls glUseProgram if not yet used for valid shader
    bool use();

    bool setUniformVec2(glm::vec2 const &vec, std::string const &name);
    bool setUniformVec3(glm::vec3 const &vec, std::string const &name);
    bool setUniformVec4(glm::vec4 const &vec, std::string const &name);
    bool setUniformArrayVec3(std::vector<glm::vec3> const &vec, std::string const &name);
    bool setUniformArrayVec4(std::vector<glm::vec4> const &vec, std::string const &name);
    bool setUniformMatrix(glm::mat3 const &mat, std::string const &name);
    bool setUniformMatrix(glm::mat4 const &mat, std::string const &name);

private:
    bool initialized_;
    bool load(std::string &result, std::string const &path);
    bool compile(GLuint shader_id, std::string const &shader_code);
    bool compile(GLuint shader_id, std::vector<std::string> const &shader_code);
    bool link(GLuint vertex_shader_id, GLuint fragment_shader_id, GLuint geometry_shader_id = 0);
    bool inUse() const;
    GLuint program_id_;

    std::string last_error_info_;

    // -1 for errors
    GLint getUniform(std::string const &name);
};
} // ns
} // ns



