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
      bool create();

      //! Create complete shader program from string
      bool create(const std::string& vertex_code, const std::string& fragment_code);
      
      //! Create complete shader program from file sources
      bool createFromFile(const std::string& vertex_file_path, const std::string& fragment_file_path);
      
      //! Shader contains a valid fragment- and vertex-shader 
      bool initialized() const {return initialized_;}

      //! For initialized()==true, the function returns a valid shader program id
      GLuint programId() const { return program_id_; }

    private:  
      bool initialized_;
      bool load(std::string& result, const std::string& path);
      bool compile(GLuint shader_id, const std::string& shader_code);
      bool link(GLuint vertex_shader_id, GLuint fragment_shader_id);

      GLuint program_id_;
    };
  } // ns
} // ns



