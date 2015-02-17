#pragma once

#include <memory>
#include "protean3d/globject.h"
#include "protean3d/types.h"
#include "protean3d/textengine/textengine.h"

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
        bool setValues(Protean3D::Triple const& begin, Protean3D::Triple const& end,
                       std::vector<Triple> const& majors, std::vector<Triple> const& minors,
                       std::vector<double> const& major_values);
        void setTicOrientation(Triple const& val);
        void setSymmetricTics(bool val);
        void setTicLength(double majorticlen, double minorticlen);
        void setNumberAnchor(TextEngine::Anchor a) {number_anchor_ = a;}

      private:
        GL::Shader shader_;
        Protean3D::TripleF begin_;
        Protean3D::TripleF end_;
        std::vector<TripleF> majors_;
        std::vector<TripleF> minors_;
        std::vector<double> majorvalues_;
        float majorticlength_ = 0.0f;
        float minorticlength_ = 0.0f;
        TextEngine::Anchor number_anchor_ = TextEngine::Anchor::BottomCenter;
        bool symtics_ = false;
        TripleF orientation_ = TripleF(1.0f, 0.0f, 0.0f);
        double excess_ = 0.0; // becomes > 1 for axes outside float range
        bool modified_ = true;

        std::unique_ptr<VBO> vbo_;
        std::shared_ptr<TextEngine> te_;

        bool updateData();

        bool majors_changed_ = true;
    };
  } // ns
} // ns
