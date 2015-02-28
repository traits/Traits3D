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

  bool initializeGL()
  {
    SurfacePlot::initializeGL();
    return loadData();
  }
  
  bool loadData()
  {
    std::vector<Traits3D::TripleF> data = Traits3D::GL::convert(broeckchen.data());

    if (!addPositionData(data, broeckchen.xSize(), broeckchen.ySize(), GL_STATIC_DRAW))
      return false;

    return setDataColor(Traits3D::ColorTable::stdColor(100)) && setMeshColor(Traits3D::Color(0.0, 0.5, 0.5, 0));
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
    
    Traits3D::QtWidget <Rosenbrock>* qtwidget 
      = new Traits3D::QtWidget <Rosenbrock>();

    qtwidget->plot3d->setBackgroundColor(Traits3D::Color(0.95f));
    qtwidget->resize(800, 600);
    qtwidget->show();
    return a.exec();
}
