#include "axis.h"

using namespace Protean3D;

Axis::Axis()
{
  init();
};

Axis::~Axis()
{
}

Axis::Axis(Triple beg, Triple end)
{
  init();
  setPosition(beg,end);
}

void Axis::init()
{
  scale_ = std::shared_ptr<Scale>(new LinearScale);

  beg_ = Triple(0.0, 0.0, 0.0);  
  end_ = beg_;
  
  majorintervals_ = 0;
  minorintervals_ = 0;
  setMajors(1);   
  setMinors(1);   
  setLimits(0,0);

  symtics_ = false;
  autoscale_ = true;
}

void Axis::setPosition(const Triple& beg, const Triple& end)
{
  beg_ = beg;
  end_ = end;
}

void Axis::setMajors(size_t val)
{
  if (val == majorintervals_)
    return;
  
  majorintervals_ = (!val) ? 1 : val; // always >= 1
}

/*!
\see LogScale::setMinors().
*/
void Axis::setMinors(size_t val)
{
  if (val == minorintervals_)
    return;

  minorintervals_ = (!val) ? 1 : val; // always >= 1
}

void Axis::setTicOrientation(double tx, double ty, double tz)
{
  setTicOrientation(Triple(tx,ty,tz));
}

void Axis::setTicOrientation(const Triple& val)
{
  orientation_ = glm::normalize(val);
}

bool Axis::prepTicCalculation(Triple& startpoint)
{
  if (isPracticallyZero(start_, stop_))
    return false;

  autostart_ = start_;
  autostop_ = stop_;

  if (autoScale()) 
  {  
    setMajors(scale_->autoscale(autostart_, autostop_, start_, stop_, majors()));
    if (isPracticallyZero(autostart_, autostop_))
      return false;
  }
  
  scale_->setLimits(start_,stop_);
  scale_->setMajors(majors());
  scale_->setMinors(minors());
  scale_->setMajorLimits(autostart_,autostop_);
  scale_->calculate();

  startpoint = end_ - beg_;

  majorpos_.clear();
  minorpos_.clear();

  return true;
}

void Axis::recalculateTics()
{
  Triple runningpoint;
  if (false==prepTicCalculation(runningpoint))
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

/*!
  Sets one of the predefined scaling types.
  \warning Too small intervals in logarithmic scales lead to  
  empty scales (or perhaps a scale only containing an isolated 
  major tic). Better switch to linear scales in such cases.
*/
void Axis::setScale(Protean3D::SCALETYPE val)
{
  switch(val) {
  case Protean3D::LINEARSCALE:
    setScale(std::shared_ptr<Protean3D::Scale>(new LinearScale));
    break;
  case Protean3D::LOG10SCALE:
    setScale(std::shared_ptr<Protean3D::Scale>(new LogScale));
    setMinors(9);
    break;
  default:
    break;
  }
}
