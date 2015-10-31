#pragma once

#include "traits3d/plot3d.h"
#include "qtwidgetbase.h"

namespace traits3d
{
//! A class
/**
  A ...

*/

template <typename P>
class EXAMPLE_EXPORT QtWidget : public QtWidgetBase
{
public:
    explicit QtWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0)
        : QtWidgetBase(std::shared_ptr<P>(new P()), parent, flags)
    {
        static_assert(
            std::is_base_of<Plot3D, P>::value
            && !std::is_same<Plot3D, P>::value
            , "wrong base class");
        plot3d = std::dynamic_pointer_cast<P>(plot_p);
    }

    std::shared_ptr<P> plot3d;
};

} // ns



