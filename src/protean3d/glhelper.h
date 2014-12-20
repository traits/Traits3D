#pragma once

#include <vector>
#include <algorithm>

#if defined PROTEAN3D_GL_IS_OPENGL
  #include <glloadgen/GL_3_3/gl_core_3_3.h>
#elif defined PROTEAN3D_GL_IS_OPENGL_ES
  #include <GLES3/gl3.h> 
#else
  #include <glloadgen/GL_3_3/gl_core_3_3.h>
#endif

#include "glm/glm.hpp"

namespace Protean3D
{
  namespace GL
  {
    /**    
     Checks, if the argument fits in a GLfloat by returning the scaling factor
     associated with values position in (+/-)[0 ... max(GLfloat) ... max(double)]
     \return m>=0, with (+/-)m*max(GLfloat) == value (>1 for values, exceeding the range of GLfloat)  
     */
    inline GLfloat excess(double value)
    {
      return (value > 0)
        ? static_cast<GLfloat>(value / std::numeric_limits<GLfloat>::max())
        : -static_cast<GLfloat>(value / std::numeric_limits<GLfloat>::max());
    }

    //! \return maximal excess for all three components
    inline GLfloat excess(glm::dvec3 value)
    {
      return std::max({ excess(value.x), excess(value.y), excess(value.z) });
    }
    
    //! \return maximal excess for val
    GLfloat excess(std::vector<glm::dvec3> const& val); 

    /**
     Scale vector by maximal excess, if exc > 1, simply convert 
     vector<glm::vec3> else
    
     \param [in,out] exc The maximal excess
     \param val          The vector to scale
    
     \return Scaled/converted vector
     */
    std::vector<glm::vec3> scale(double& exc, std::vector<glm::dvec3> const& val);
  }
}