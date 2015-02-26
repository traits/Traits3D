#include "traits3d/helper.h"
#include "traits3d/axis.h"

Traits3D::Axis::Axis()
{
  init();
};

Traits3D::Axis::~Axis()
{
}

Traits3D::Axis::Axis(Triple beg, Triple end)
{
  init();
  setPosition(beg,end);
}

void Traits3D::Axis::init()
{
  scale_ = std::shared_ptr<Scale>(new LinearScale);

  number_font_ = FontInfo("OpenSans Regular", 24);
  label_font_ = FontInfo("OpenSans Italic", 36);

  tic_orientation_ = Triple(1.0, 0.0, 0.0);
  scale_number_anchor_ = TextEngine::Anchor::Center;
  label_anchor_ = TextEngine::Anchor::Center;
}

void Traits3D::Axis::setPosition(const Triple& beg, const Triple& end)
{
  axis_origin_ = beg;
  axis_end_ = end;
}

void Traits3D::Axis::setMajors(size_t val)
{
  if (val == majorintervals_)
    return;

  majorintervals_ = (!val) ? 1 : val; // always >= 1
}

/*!
\see LogScale::setMinors().
*/
void Traits3D::Axis::setMinors(size_t val)
{
  if (val == minorintervals_)
    return;

  minorintervals_ = (!val) ? 1 : val; // always >= 1
}

void Traits3D::Axis::setTicLength(double majorl, double minorl)
{
  len_major_tics_ = majorl;
  len_minor_tics_ = minorl;
}

void Traits3D::Axis::setTicOrientation(double tx, double ty, double tz)
{
  setTicOrientation(Triple(tx,ty,tz));
}

void Traits3D::Axis::setTicOrientation(const Triple& val)
{
  tic_orientation_ = (equal(val, Triple(0.0,0.0,0.0)))
  ? Triple(1.0, 0.0, 0.0)
  : glm::normalize(val);
}

bool Traits3D::Axis::prepTicCalculation(Triple& startpoint)
{
  if (equal(start_, stop_))
    return false;

  autostart_ = start_;
  autostop_ = stop_;

  if (autoScale())
  {
    setMajors(scale_->autoscale(autostart_, autostop_, start_, stop_, majors()));
    if (equal(autostart_, autostop_))
      return false;
  }

  scale_->setLimits(start_,stop_);
  scale_->setMajors(majors());
  scale_->setMinors(minors());
  scale_->setMajorLimits(autostart_,autostop_);
  scale_->calculate();

  startpoint = axis_end_ - axis_origin_;

  return true;
}

void Traits3D::Axis::recalculateTics()
{
  Triple runningpoint;
  major_positions_.clear();
  minor_positions_.clear();

  if (!draw_tics_ || false == prepTicCalculation(runningpoint))
    return;

  unsigned int i;

  for (i = 0; i != scale_->majors_p.size(); ++i)
  {
    double t = (scale_->majors_p[i] - start_) / (stop_-start_);
    major_positions_.push_back(axis_origin_ + t * runningpoint);
  }
  for (i = 0; i != scale_->minors_p.size(); ++i)
  {
    double t = (scale_->minors_p[i] - start_) / (stop_-start_);
    minor_positions_.push_back(axis_origin_ + t * runningpoint);
  }
}

void Traits3D::Axis::setNumberFont(Traits3D::FontInfo const& font_info)
{
  number_font_ = font_info;
}

void Traits3D::Axis::setNumberColor(Color const& col)
{
  number_color_ = col;
}

void Traits3D::Axis::setLabelFont(Traits3D::FontInfo const& font_info)
{
  label_font_ = font_info;
}

void Traits3D::Axis::setLabelText(std::string const& val)
{
  label_text_ = val;
}

/*!
  Sets label position in conjunction with an anchoring strategy
*/
void Traits3D::Axis::setLabelPosition(const Traits3D::Triple& pos, Traits3D::TextEngine::Anchor a)
{
  label_position_ = pos;
  label_anchor_ = a;
}

//! Sets color for label
void Traits3D::Axis::setLabelColor(Traits3D::Color const& val)
{
  label_color_ = val;
}
 
/*
  Sets one of the predefined scaling types.
  \warning Too small intervals in logarithmic scales lead to
  empty scales (or perhaps a scale only containing an isolated
  major tic). Better switch to linear scales in such cases.
*/
void Traits3D::Axis::setScale(Traits3D::SCALETYPE val)
{
  switch(val) {
  case Traits3D::LINEARSCALE:
    setScale(std::shared_ptr<Traits3D::Scale>(new LinearScale));
    break;
  case Traits3D::LOG10SCALE:
    setScale(std::shared_ptr<Traits3D::Scale>(new LogScale));
    setMinors(9);
    break;
  default:
    break;
  }
}

void Traits3D::Axis::draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix)
{
  //todo performance!
  recalculateTics();
  globject_p->setSymmetricTics(symmetric_tics_);
  globject_p->setTicOrientation(tic_orientation_);
  globject_p->setTicLength(len_major_tics_, len_minor_tics_);
  globject_p->setValues(axis_origin_, axis_end_, major_positions_, minor_positions_, scale_->majors_p);
  globject_p->setNumberAnchor(scale_number_anchor_);
  globject_p->setLabelFont(label_font_);
  globject_p->setNumberFont(number_font_);

  //end todo
  globject_p->draw(proj_matrix, mv_matrix);
}

bool Traits3D::Axis::initializeGL()
{
  globject_p = std::make_shared<GL::AxisObject>();
  return (globject_p) ? true : false;
}