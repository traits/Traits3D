#pragma once

#include <memory>
#include "traits3d/glbase/globject.h"
#include "traits3d/types.h"
#include "traits3d/fonts/fontinfo.h"
#include "traits3d/textengine/textengine.h"

namespace Traits3D
{
  class TextEngine;

  namespace GL
  {
    class AxisObject : public GL::Object
    {
      public:
        AxisObject();

        void draw(GL::Transformation const& matrices) override;
        bool setValues(Traits3D::Triple const& begin, Traits3D::Triple const& end,
                       std::vector<Triple> const& majors, std::vector<Triple> const& minors,
                       std::vector<double> const& major_values);
        
        void showTics(bool val);
        void setTicOrientation(Triple const& val);
        void setSymmetricTics(bool val);
        void setTicLength(double majorticlen, double minorticlen);
        void setColor(Color const& val);

        void showLabel(bool val);
        void setLabelFont(Traits3D::FontInfo const& font_info);
        void setLabelText(std::string const& val);
        void setLabelPosition(Triple const& pos, TextEngine::Anchor a);
        void setLabelColor(Color const& val);
        void adjustLabel(int val);

        void showNumbers(bool val);
        void setNumberFont(Traits3D::FontInfo const& font_info);
        void setNumberColor(Color const& val);
        void setNumberAnchor(TextEngine::Anchor a) { number_anchor_ = a; }
        void adjustNumbers(int val);


      private:
        GL::Shader shader_;
        Traits3D::TripleF begin_;
        Traits3D::TripleF end_;
        std::vector<TripleF> majors_;
        std::vector<TripleF> minors_;
        std::vector<double> major_values_;
        float majorticlength_ = 0.0f;
        float minorticlength_ = 0.0f;
         bool symtics_ = false;
        TripleF orientation_ = TripleF(1.0f, 0.0f, 0.0f);
        double excess_ = 0.0; // becomes > 1 for axes outside float range
        bool modified_ = true;

        std::unique_ptr<VBO> vbo_;
        std::shared_ptr<TextEngine> te_;

        bool updateData();

        FontInfo label_font_info_;
        FontInfo number_font_info_;
        Color number_color_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
        Color label_color_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
        Color axis_color_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
        int number_gap_ = 0;
        int label_gap_ = 0;

        bool show_numbers_ = false;
        bool show_tics_ = false;
        bool show_label_ = false;

        Triple label_position_;
        std::string label_text_;
        TextEngine::Anchor label_anchor_ = TextEngine::Anchor::Center;;
        TextEngine::Anchor number_anchor_ = TextEngine::Anchor::BottomCenter;
    };
  } // ns
} // ns
