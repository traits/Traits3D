#pragma once

#include <memory>
#include "traits3d/types.h"
#include "traits3d/autoscaler.h"

namespace Traits3D
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
  class TRAITS3D_EXPORT Scale
  {
    friend class Axis;   
    public:
      Scale();
      virtual ~Scale(){}

    protected:
      //virtual Traits3D::Label::String ticLabel(unsigned int idx) const;

      virtual void setLimits(double start, double stop); 
      virtual void setMajors(size_t val) {majorintervals_p=val;} //!< Sets number of major intervals
      virtual void setMinors(size_t val) {minorintervals_p=val;} //!< Sets number of minor intervals per major interval
      virtual void setMajorLimits(double start, double stop);

      size_t majors() const {return majorintervals_p;} //!< Returns number of major intervals
      size_t minors() const {return minorintervals_p;} //!< Returns number of minor intervals per major interval

      //! This function should setup the 2 vectors for major and minor positions;
      virtual void calculate() = 0;
      virtual size_t autoscale(double& a, double& b, double start, double stop, size_t ivals);

      std::vector<double> majors_p, minors_p; 
      double start_p, stop_p;
      size_t majorintervals_p, minorintervals_p;
      double mstart_p, mstop_p;
  };

  //! The standard (1:1) mapping class for axis numbering
  class TRAITS3D_EXPORT LinearScale : public Scale
  {
    friend class Axis;

    protected:
      size_t autoscale(double& a, double& b, double start, double stop, size_t ivals) override;
      void calculate() override;
      LinearAutoScaler autoscaler_p;
  };

  //! log10 scale
  class TRAITS3D_EXPORT LogScale : public Scale
  {
    friend class Axis;
    //friend struct ValuePtrTraits<Scale>;
    protected:
      //Traits3D::Label::String ticLabel(unsigned int idx) const;
      void setMinors(size_t val) override;
      //! Standard ctor
      LogScale();
      void calculate() override;
    private:
      void setupCounter(double& k, int& step);
  };
} // ns



