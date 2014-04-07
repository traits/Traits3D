#pragma once

#include <GL/glew.h>
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
      bool create(GLuint& program_id);

      //! Create complete shader program from string
      bool create(GLuint& program_id, const std::string& vertex_code, const std::string& fragment_code);
      
      //! Create complete shader program from file sources
      bool createFromFile(GLuint& program_id, const std::string& vertex_file_path, const std::string& fragment_file_path);
      
      //! Shader contains a valid fragment- and vertex-shader 
      bool initialized() const {return initialized_;}

    private:  
      bool initialized_;
      bool load(std::string& result, const std::string& path);
      bool compile(GLuint shader_id, const std::string& shader_code);
      bool link(GLuint& program_id, GLuint vertex_shader_id, GLuint fragment_shader_id);
    };
  } // ns
} // ns



