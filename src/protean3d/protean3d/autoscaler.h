#pragma once

#include <vector>
#include "global.h"

namespace Protean3D
{

//! ABC for autoscaler
class PROTEAN3D_EXPORT AutoScaler
{
protected:
  //! To implement from subclasses
  virtual size_t execute(double& a, double& b, double start, double stop, size_t ivals) = 0;
  virtual ~AutoScaler(){}
};

//! Automatic beautifying of linear scales
class PROTEAN3D_EXPORT LinearAutoScaler : public AutoScaler
{
friend class LinearScale;
protected:
  LinearAutoScaler();
  explicit LinearAutoScaler(std::vector<double>& mantisses);
  size_t execute(double& a, double& b, double start, double stop, size_t ivals) override;

private:
	
  double start_, stop_;
  size_t intervals_; 

  void init(double start, double stop, size_t ivals);
  double anchorvalue(double start, double mantisse, int exponent);
  int segments(int& l_intervals, int& r_intervals, double start, double stop, double anchor, double mantissa, int exponent);
  std::vector<double> mantissi_;
};

} // ns


