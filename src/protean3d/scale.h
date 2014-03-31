#pragma once

#include <memory>
#include "types.h"
//#include "label.h"
#include "autoscaler.h"

namespace Protean3D
{

/*! 
The class encapsulates non-visual scales. 
She is utilized by Axis and also collaborates closely with AutoScaler.
A Scale allows control over all aspects of tic generation including 
arbitrary transformations of tic values into corresponding strings. 
The strings contain what eventually will be shown as tic labels.\n
Standard linear and logarithmic scales have been integrated yet into the Axis 
interface. User-defined axes can be derived from Scale, LinearScale et al.
*/
class PROTEAN3D_EXPORT Scale
{
  friend class Axis;   
  public:
    Scale();
    virtual ~Scale(){}

protected:
    //virtual Protean3D::Label::String ticLabel(unsigned int idx) const;

    virtual void setLimits(double start, double stop); 
    virtual void setMajors(int val) {majorintervals_p=val;} //!< Sets number of major intervals
    virtual void setMinors(int val) {minorintervals_p=val;} //!< Sets number of minor intervals per major interval
    virtual void setMajorLimits(double start, double stop);

    int majors() const {return majorintervals_p;} //!< Returns major intervals
    int minors() const {return minorintervals_p;} //!< Returns minor intervals

    //! This function should setup the 2 vectors for major and minor positions;
    virtual void calculate() = 0;
    virtual int autoscale(double& a, double& b, double start, double stop, int ivals);

    std::vector<double> majors_p, minors_p; 
    double start_p, stop_p;
    int majorintervals_p, minorintervals_p;
    double mstart_p, mstop_p;
};

//! The standard (1:1) mapping class for axis numbering
class PROTEAN3D_EXPORT LinearScale : public Scale
{
  friend class Axis;
  //friend struct ValuePtrTraits<Scale>;
  protected:
    int autoscale(double& a, double& b, double start, double stop, int ivals);
    void calculate();
    LinearAutoScaler autoscaler_p;
};

//! log10 scale
class PROTEAN3D_EXPORT LogScale : public Scale
{
  friend class Axis;
  //friend struct ValuePtrTraits<Scale>;
  protected:
    //Protean3D::Label::String ticLabel(unsigned int idx) const;
    void setMinors(int val);
    //! Standard ctor
    LogScale();
    void calculate();
  private:
    void setupCounter(double& k, int& step);
};

} // namespace Protean3D



