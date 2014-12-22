//-----------------------------------------------------------------
//              simpleplot.cpp
//
//      A simple example which shows how to use SurfacePlot
//-----------------------------------------------------------------

#include <math.h>
#include <qapplication.h>
#include "qtwidget.hh"
#include "protean3d/surfaceplot.h"


using namespace Protean3D;

class Rosenbrock : public SurfacePlot
{
public:
  const size_t xsize = 41;
  const size_t ysize = 31;
  const float xmin = -1.73f;
  const float xmax = 1.5f;
  const float ymin = -1.5f;
  const float ymax = 1.5f;


  bool loadData()
  {
    float dx = (xmax - xmin) / (xsize - 1);
    float dy = (ymax - ymin) / (ysize - 1);
    float curr_x = ymin;
    float curr_y = xmin;

    std::vector<glm::vec3> data(xsize*ysize);
    auto k = 0;
    for (auto y = 0; y != ysize; ++y)
    {
      for (auto x = 0; x != xsize; ++x)
      {
        data[k].x = curr_x;
        data[k].y = curr_y;
        data[k].x = getZ(x,y);
        curr_x += dx;
        ++k;
      }
      curr_y += dy;
      curr_x = xmin;
    }
    return addPositionData(data, xsize, ysize, GL_STATIC_DRAW);
  }

private:
  double getZ(double x, double y)
  {
    return std::max<float>(-10.0f, log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8);
  }
};


class Plot : public QtWidget<Rosenbrock>
{
public:
    Plot();
};


Plot::Plot()
{
  plot().setRotation(30, 0, 15);
  plot().setScale(1, 1, 1);
  plot().setShift(0.15, 0, 0);
  plot().setZoom(0.9);

//  updateData();
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    
    Plot* plot = new Plot();

    plot->plot().initializedGL();

    plot->plot().loadData();


    plot->resize(800, 600);
    plot->show();
    return a.exec();
}
