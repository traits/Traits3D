#pragma once

//! Portability classes providing transparent Qt3/4 support

#include <QMouseEvent>

namespace Traits3D
{   
  //! This class creates a (mouse-button,modifier) pair
  class MouseState
  {
  public:
    MouseState(Qt::MouseButtons mb = Qt::NoButton, Qt::KeyboardModifiers km = Qt::NoModifier)
      : mb_(mb), km_(km)
    {
    }

    MouseState(Qt::MouseButton mb, Qt::KeyboardModifiers km = Qt::NoModifier)
      : mb_(mb), km_(km)
    {
    }

    bool operator==(const MouseState& ms)
    {
      return mb_ == ms.mb_ && km_ == ms.km_;
    }

    bool operator!=(const MouseState& ms)
    {
      return !operator==(ms);
    }

  private:
    Qt::MouseButtons mb_;
    Qt::KeyboardModifiers km_;
  };
  
  //! This class creates a (key-button,modifier) pair
  class KeyboardState
  {
  public:
    KeyboardState(int key = Qt::Key_unknown, Qt::KeyboardModifiers km = Qt::NoModifier)
      : key_(key), km_(km)
    {
    }

    bool operator==(const KeyboardState& ms)
    {
      return key_ == ms.key_ && km_ == ms.km_;
    }

    bool operator!=(const KeyboardState& ms)
    {
      return !operator==(ms);
    }

  private:
    int key_;
    Qt::KeyboardModifiers km_;
  };
} // ns


