//-----------------------------------------------------------------
//              simpleplot.cpp
//
//      A simple example which shows how to use SurfacePlot
//-----------------------------------------------------------------

#include <math.h>
#include <qapplication.h>
#include "qtwidget.hh"
#include "traits3d/function.h"
#include "traits3d/surfaceplot.h"
#include <QOpenGLContext>


class Broeckchen : public Traits3D::Function
{
public:
  Broeckchen()
  {
    setDomainResolution(41, 31);
    setDomain(-0.5, 1.5, -1.5, 1.5);
    //setRange(-10, 20);
  }

  double operator()(double x, double y)
  {
    return std::max<float>(-1.0f, log((1 - x)*(1 - x) + 100 * (y - x*x)*(y - x*x)) / 8);
  }
};

class Rosenbrock : public Traits3D::SurfacePlot
{
public:
  Broeckchen broeckchen;

  Rosenbrock()
  {
    setRotation(Traits3D::deg2rad(30), 0, Traits3D::deg2rad(15));
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

  bool initializeGL()
  {
    SurfacePlot::initializeGL();
    setTitle("Simple Plot");
    setBackgroundColor(Traits3D::Color(0.95f));
    return loadData();
  }
  
  bool loadData()
  {
    if (!addPositionData(broeckchen.dataF()))
      return false;

    setDataColor(Traits3D::ColorTable::stdColor(100)); 
    return setMeshColor(Traits3D::Color(0.0, 0.5, 0.5, 0));
  }

  //void updateData() override
  //{
  //  //glEnable(GL_BLEND);
  //  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //  //glEnable(GL_LINE_SMOOTH);
  //  updatePositionData(data_);
  //}
};


int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    
    Traits3D::QtWidget <Rosenbrock> rosenbrock;

    rosenbrock.resize(800, 600);
    rosenbrock.show();
    return a.exec();
}
