#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#if defined TRAITS3D_GL_IS_OPENGL
  #if TRAITS3D_GL_MAJOR > 3
    #include "traits3d/opengl/gl_core_4_2.h"
  #else
    #include "traits3d/opengl/gl_core_3_3.h"
  #endif
#elif defined TRAITS3D_GL_IS_OPENGL_ES
  #include <GLES3/gl3.h>
#else
  #include "traits3d/opengl/gl_core_3_3.h"
#endif

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Traits3D
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
