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

  beg_ = Triple(0.0, 0.0, 0.0);
  end_ = beg_;

  majorintervals_ = 0;
  minorintervals_ = 0;
  setMajors(1);
  setMinors(1);
  setLimits(0,0);

  setTicOrientation(0.0, 0.0, 0.0);
  setTicLength(0.0, 0.0);
  setColor(Color(0,0,0,0));
  //setLineWidth(1.0);
  symtics_ = false;
  draw_numbers_ = false;
  draw_label_ = false;

  draw_tics_ = false;
  autoscale_ = true;
  numbercolor_ = Color(0, 0, 0, 0);

  setNumberAnchor(TextEngine::Anchor::Center);

  numbergap_ = 0;
}

void Traits3D::Axis::setPosition(const Triple& beg, const Triple& end)
{
  beg_ = beg;
  end_ = end;
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
  lmaj_ = majorl;
  lmin_ = minorl;
}

void Traits3D::Axis::setTicOrientation(double tx, double ty, double tz)
{
  setTicOrientation(Triple(tx,ty,tz));
}

void Traits3D::Axis::setTicOrientation(const Triple& val)
{
  orientation_ = glm::normalize(val);
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

  startpoint = end_ - beg_;

  return true;
}

void Traits3D::Axis::recalculateTics()
{
  Triple runningpoint;
  majorpos_.clear();
  minorpos_.clear();

  if (!draw_tics_ || false == prepTicCalculation(runningpoint))
    return;

  unsigned int i;

  for (i = 0; i != scale_->majors_p.size(); ++i)
  {
    double t = (scale_->majors_p[i] - start_) / (stop_-start_);
    majorpos_.push_back(beg_ + t * runningpoint);
  }
  for (i = 0; i != scale_->minors_p.size(); ++i)
  {
    double t = (scale_->minors_p[i] - start_) / (stop_-start_);
    minorpos_.push_back(beg_ + t * runningpoint);
  }
}

void Traits3D::Axis::setNumberColor(Color const& col)
{
  numbercolor_ = col;
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
  globject_p->setSymmetricTics(symtics_);
  globject_p->setTicOrientation(orientation_);
  globject_p->setTicLength(lmaj_, lmin_);
  globject_p->setValues(beg_, end_, majorpos_, minorpos_, scale_->majors_p);
  globject_p->setNumberAnchor(scaleNumberAnchor_);
  //end todo
  globject_p->draw(proj_matrix, mv_matrix);
}

bool Traits3D::Axis::initializeGL()
{
  globject_p = std::make_shared<GL::AxisObject>();
  return (globject_p) ? true : false;
}