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
    setMeshSize(41, 31);
    setDomain(-0.5, 1.5, -1.5, 1.5);
    //setRange(-10, 20);
  }

  double operator()(double x, double y)
  {
    return std::max<float>(-1.0f, log((1 - x)*(1 - x) + 100 * (y - x*x)*(y - x*x)) / 8);
  }

  std::vector<Traits3D::TripleF> fullData()
  {
    const std::vector<double>& dvec = data();

    std::vector<Traits3D::TripleF> fdata(dvec.size());

    size_t xsize = uMeshSize();
    size_t ysize = vMeshSize();
    Traits3D::Box h = hull();
    double dx = (h.maxVertex.x - h.minVertex.x) / (xsize - 1);
    double dy = (h.maxVertex.y - h.minVertex.y) / (ysize - 1);


    for (size_t i = 0; i != dvec.size(); ++i)
    {
      fdata[i] = Traits3D::TripleF(
        static_cast<float>(h.minVertex.x + dx*(i % xsize)),
        static_cast<float>(h.minVertex.y + dy*(i / xsize)),
        static_cast<float>(dvec[i])
        );
    }
    return fdata;
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
    std::vector<Traits3D::TripleF> data = broeckchen.fullData();

    size_t xsize = broeckchen.uMeshSize();
    size_t ysize = broeckchen.vMeshSize();


    if (!addPositionData(data, xsize, ysize, GL_STATIC_DRAW))
      return false;

    size_t size = data.size();
    float fsize = size;
    Traits3D::ColorVector colors(size);
    for (size_t i = 0; i != size; ++i)
    {
      Traits3D::Color& elem = colors[i];
      elem.r = i / fsize;
      elem.g = i / fsize / 4;
      elem.b = 1 - i / fsize;
      elem.a = 1.0f;
    }

    return addDataColor(colors) && addMeshColor(Traits3D::Color(0.0, 0.5, 0.5, 0));
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
