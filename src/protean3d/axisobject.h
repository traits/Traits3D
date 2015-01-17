#pragma once

#include <memory>
#include "globject.h"

namespace Protean3D
{
  class TextEngine;

  namespace GL
  {
    class AxisObject : public GL::Object
    {
    public:
      AxisObject();

      void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix) override;
      void setValues(Protean3D::Triple const& begin, Protean3D::Triple const& end, 
        std::vector<Triple> const& majors, std::vector<Triple> const& minors);
      void setTicOrientation(Triple const& val);
      void setSymmetricTics(bool val);
      void setTicLength(double majorticlen, double minorticlen);

    private:
      GL::Shader shader_;
      Protean3D::TripleF begin_;
      Protean3D::TripleF end_;
      std::vector<TripleF> majors_;
      std::vector<TripleF> minors_;
      float majorticlength_ = 0.0f;
      float minorticlength_ = 0.0f;
      bool symtics_ = false;
      TripleF orientation_ = TripleF(1.0f, 0.0f, 0.0f);
      double excess_ = 0.0; // becomes > 1 for axes outside float range
      bool modified_ = true;

      std::unique_ptr<VBO> vbo_;
      std::shared_ptr<TextEngine> te_;

      bool updateData();
    };
  } // ns
} // ns
