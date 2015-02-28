#pragma once

#include <array>
#include "traits3d/colortable.h"
#include "traits3d/coordinates.h"
#include "traits3d/dataobject.h"
#include "traits3d/extglwidget.h"
#include "traits3d/textengine/textengine.h"


namespace Traits3D
{
  //! Base class for all plotting widgets
  /*!
  Plot3D handles all the common features for plotting widgets beyond the low-level extensions of
  ExtGLWidget - coordinate system, labeling and more. It contains some pure virtual functions and is -
  in this respect - an abstract base class. It's nevertheless no pure interface.
  The class provides interfaces for basic data controlled color allocation.
  */
  class TRAITS3D_EXPORT Plot3D : public ExtGLWidget
  {
    public:
      Plot3D();
      virtual ~Plot3D();

      bool initializeGL() override;

      void draw();
      void updateData() override {}
      void setBackgroundColor(Color const& val); //!< Sets widgets background color
      Color backgroundRGBAColor() const {return bgcolor_;} //!< Returns the widgets background color
      std::shared_ptr<Coordinates> coordinates() { return coordinates_p; }

      //void setTitlePosition(double rely, double relx = 0.5);
      void setTitle(std::string const& val); //!< Set caption text (one row only)

    protected:
      Box hull_p;
      std::unique_ptr<GL::DataObject> data_object_p;
      std::shared_ptr<Coordinates> coordinates_p;

      // labels
      std::shared_ptr<TextEngine> text_engine_p;

      glm::mat4 projection_matrix_p;
      glm::mat4  modelview_matrix_p;

    private:
      Color bgcolor_;
      std::string title_;
  };
} // ns
