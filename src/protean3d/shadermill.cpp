#include "shadermill.h"

const std::string Protean3D::GL::ShaderMill::os_switch_ =
#ifdef GL_ES_VERSION_3_0
"#version 100\n"
#else
"#version 150\n"
#endif
;

const std::string Protean3D::GL::ShaderMill::proj_matrix  = "proj_matrix";
const std::string Protean3D::GL::ShaderMill::mv_matrix    = "mv_matrix";

const std::string Protean3D::GL::ShaderMill::matrix_preamble_ =
  std::string("uniform mat4 ") + proj_matrix + ";\n"
  + "uniform mat4 " + mv_matrix + ";\n";

const std::string Protean3D::GL::ShaderMill::main_begin_ = "void main()\n{\n";
const std::string Protean3D::GL::ShaderMill::main_end_ = "}\n";


Protean3D::GL::ShaderMill::ShaderMill()
{
  v_standard_txt_ =
    os_switch_
    + matrix_preamble_
    + "in float x;\n"
    + "in float y;\n"
    + "in float z;\n"
    //+ "in vec4  v_in_color;\n"
    + "out vec4  v_out_color;\n"
    + "\n" 
    + main_begin_ 
    + "   gl_Position = proj_matrix * mv_matrix * vec4(x, y, z, 1.0);\n"
    + "   v_out_color = vec4(y, y, y, 1.0);\n"
    //+ "   v_out_color = v_in_color;\n"
    + main_end_;

  f_standard_txt_ =
    os_switch_
    + "in vec4 v_out_color; \n"
    + "out vec4 gl_FragColor;\n"
    + main_begin_
    + "  gl_FragColor = v_out_color; \n"
    + main_end_;
}

std::string Protean3D::GL::ShaderMill::vertexCode() const
{
  return v_standard_txt_;
}

std::string Protean3D::GL::ShaderMill::fragmentCode() const
{
  return f_standard_txt_;
}




