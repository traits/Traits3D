//-----------------------------------------------------------------
//              simpleplot.cpp
//
//      A simple example which shows how to use SurfacePlot
//-----------------------------------------------------------------

#include <math.h>
#include <qapplication.h>
#include "qtwidget.hh"
#include "protean3d/surfaceplot.h"

class Rosenbrock : public Protean3D::SurfacePlot
{
public:
 size_t xsize = 41;
 size_t ysize = 31;
 float xmin = -1.73f;
 float xmax = 1.5f;
 float ymin = -1.5f;
 float ymax = 1.5f;

  Rosenbrock()
  {
    data_.resize(xsize*ysize);
    setRotation(30, 0, 15);
    setScale(1, 1, 1);
    setShift(0.15f, 0, 0);
    setZoom(0.9f);     
    //setScale(1.0, 1.0, 0.5);
    
    //coordinates_p->setStyle(FRAME);
    for (unsigned i = 0; i != coordinates_p->axes.size(); ++i)
    {
      coordinates_p->axes[i].setMajors(7);
      coordinates_p->axes[i].setMinors(4);
    }
  }

  bool loadData()
  {
    float dx = (xmax - xmin) / (xsize - 1);
    float dy = (ymax - ymin) / (ysize - 1);
    float curr_x = xmin;
    float curr_y = ymin;

    auto k = 0;
    for (size_t y = 0; y != ysize; ++y)
    {
      for (size_t x = 0; x != xsize; ++x)
      {
        data_[k].x = curr_x;
        data_[k].y = curr_y;
        data_[k].z = getZ(x,y);
        curr_x += dx;
        ++k;
      }
      curr_y += dy;
      curr_x = xmin;
    }
    if (!addPositionData(data_, xsize, ysize, GL_STATIC_DRAW))
      return false;

    size_t size = data_.size();
    float fsize = size;
    Protean3D::ColorVector colors(size);
    for (size_t i = 0; i != size; ++i)
    {
      glm::vec4& elem = colors[i];
      elem.r = i / fsize;
      elem.g = i / fsize / 4;
      elem.b = 1 - i / fsize;
      elem.a = 1.0f;
    }

    return addDataColor(colors) && addMeshColor(glm::vec4(0, 0, 0, 0));
  }

  void updateData() override
  {
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_LINE_SMOOTH);
    updatePositionData(data_);
  }

private:
  std::vector<glm::vec3> data_;
  double getZ(double x, double y)
  {
    return std::max<float>(-1.0f, log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8);
  }
};


int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    
    Protean3D::QtWidget <Rosenbrock>* qtwidget 
      = new Protean3D::QtWidget <Rosenbrock>();

    qtwidget->resize(800, 600);
    qtwidget->show();
    //todo cannot call before show, because Qt doesn't initialize
    // OpenGL up to this point
    qtwidget->plot3d->loadData();
    qtwidget->plot3d->setBackgroundColor(Protean3D::Color(0.95f));
    return a.exec();
}
