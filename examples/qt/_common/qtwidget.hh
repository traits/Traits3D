#pragma once

#include "protean3d/surfaceplot.h"
#include "qtwidgetbase.h"

namespace Protean3D
{
//! A class 
/**
  A ...
  
*/

template <typename P>
class EXAMPLE_EXPORT QtWidget : public QtWidgetBase
{
public:
  explicit QtWidget(QWidget * parent = 0, const QGLWidget * shareWidget = 0)
    : QtWidgetBase(std::shared_ptr<P>(new P()), parent, shareWidget)
  {}

  P& plot() {return *std::dynamic_pointer_cast<P>(plot_p);}
  const P& plot() const {return *std::dynamic_pointer_cast<P>(plot_p);}
};

} // ns

  

