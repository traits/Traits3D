#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#if defined PROTEAN3D_GL_IS_OPENGL
  #if PROTEAN3D_GL_MAJOR > 3
    #include <glloadgen/GL_4_2/gl_core_4_2.h>
  #else
    #include <glloadgen/GL_3_3/gl_core_3_3.h>
  #endif
#elif defined PROTEAN3D_GL_IS_OPENGL_ES
  #include <GLES3/gl3.h>
#else
  #include <glloadgen/GL_3_3/gl_core_3_3.h>
#endif

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Protean3D
{
  namespace GL
  {

    inline void printGlError()
    {
      GLenum err = glGetError();

      switch (err)
      {
      case GL_INVALID_ENUM:
        std::cerr << "GL_INVALID_ENUM" << "\n";
        break;
      case GL_INVALID_VALUE:
        std::cerr << "GL_INVALID_VALUE" << "\n";
        break;
      case GL_INVALID_OPERATION:
        std::cerr << "GL_INVALID_OPERATION" << "\n";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << "\n";
        break;
      case GL_OUT_OF_MEMORY:
        std::cerr << "GL_OUT_OF_MEMORY" << "\n";
        break;
      }
    }

 /*   bool error()
    {
      GLenum err;
      while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << err;
      }
    }*/

    inline glm::ivec4 viewPort()
    {
      glm::ivec4 viewport;
      glGetIntegerv(GL_VIEWPORT, glm::value_ptr(viewport)); // x,y,w,h
      return viewport;
    }

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
     Scale vector by maximal excess, if exc > 1; 
     simply convert to vector<glm::vec3> else
    
     \param [in,out] exc The maximal excess
     \param val          The vector to scale
    
     \return Scaled/converted vector
     */
    std::vector<glm::vec3> scale(double& exc, std::vector<glm::dvec3> const& val);
    
    //! Enforce scaling of val with 2nd argument 
    std::vector<glm::vec3> scale(std::vector<glm::dvec3> const& val, double excess);
    //! Converts value into vec3 vector - only casts are applied
    std::vector<glm::vec3> convert(std::vector<glm::dvec3> const& val);

    //! simplified glut routine (glUnProject): windows coordinates_p --> object coordinates_p 
    inline glm::vec3 ViewPort2World(glm::vec3 const& obj, glm::mat4 const& mv, glm::mat4 const& proj, glm::ivec4 const& viewport)
    {
      return glm::unProject(obj, mv, proj, viewport);
    }

    //! simplified glut routine (glProject): object coordinates_p --> windows coordinates_p 
    inline glm::vec3 World2ViewPort(glm::vec3 const& win, glm::mat4 const& mv, glm::mat4 const& proj, glm::ivec4 const& viewport)
    {
      return glm::project(win, mv, proj, viewport);
    }

    //! simplified glut routine (glUnProject): windows coordinates_p --> object coordinates_p 
    inline glm::dvec3 ViewPort2World(glm::dvec3 const& obj, glm::dmat4 const& mv, glm::dmat4 const& proj, glm::ivec4 const& viewport)
    {
      return glm::unProject(obj, mv, proj, viewport);
    }

    //! simplified glut routine (glProject): object coordinates_p --> windows coordinates_p 
    inline glm::dvec3 World2ViewPort(glm::dvec3 const& win, glm::dmat4 const& mv, glm::dmat4 const& proj, glm::ivec4 const& viewport)
    {
      return glm::project(win, mv, proj, viewport);
    }

    //! RAII class for GL states
    class State
    {
    public:
      //! Create maintainer for state 'state_enum'
      explicit State(GLenum state_enum)
        : state_enum_(state_enum),
        enabled_at_start_(glIsEnabled(state_enum))
      {
        current_state_ = enabled_at_start_;
      }

      State(GLenum state_enum, GLboolean enable_state)
        : state_enum_(state_enum),
        enabled_at_start_(glIsEnabled(state_enum))
      {
        current_state_ = enabled_at_start_;
        if (GL_TRUE == enable_state)
          enable();
        else
          disable();
      }

      //! Restore state from objects creation
      ~State()
      {
        if (enabled_at_start_)
          enable();
        else
          disable();
      }

      //! enable state temporarily 
      void enable()
      {
        if (current_state_)
          return;
        
        glEnable(state_enum_);
        current_state_ = true;
      }

      //! disable state temporarily 
      void disable()
      {
        if (!current_state_)
          return;

        glDisable(state_enum_);
        current_state_ = false;
      }

    private:
      const GLenum state_enum_;
      const GLboolean enabled_at_start_;
      GLboolean current_state_;
    };
  }
}
