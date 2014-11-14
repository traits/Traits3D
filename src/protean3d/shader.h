#pragma once

#include "glhelper.h"
#include "types.h"


namespace Protean3D
{
  namespace GL
  {
    //! Shader program, containing various GLSL shaders
    class PROTEAN3D_EXPORT Shader
    {
    public:
      Shader();

      //! Create complete shader program with standard shaders
      bool create();

      //! Create complete shader program from string
      bool create(std::string const& vertex_code, std::string const& fragment_code);
      
      //! Create complete shader program from file sources
      bool createFromFile(std::string const& vertex_file_path, std::string const& fragment_file_path);
      
      //! Shader contains a valid fragment- and vertex-shader 
      bool initialized() const {return initialized_;}

      //! For initialized()==true, the function returns a valid shader program id
      GLuint programId() const { return program_id_; }

      //! calls glUseProgram for valid shader
      bool use();
      
      bool setUniformMatrix(glm::mat4 const& mat, std::string const& name);
      bool setUniformVec4(glm::vec4 const& vec, std::string const& name);

    private:  
      bool initialized_;
      bool load(std::string& result, std::string const& path);
      bool compile(GLuint shader_id, std::string const& shader_code);
      bool link(GLuint vertex_shader_id, GLuint fragment_shader_id);
      GLuint program_id_;
    };
  } // ns
} // ns



