  //-----------------------------------------------------------------
  //              simpleplot.cpp
  //
  //      A simple example which shows how to use SurfacePlot
  //-----------------------------------------------------------------

  #include <math.h>
  #include <qapplication.h>
  #include <protean3d/qtwidget.hh>
  #include <protean3d/function.h>
  

  using namespace Protean3D;

  class Rosenbrock : public Function
  {
  public:

    Rosenbrock(SurfacePlot& pw)
    :Function(pw)
    {
    }

    double operator()(double x, double y)
    {
      return log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8;
    }
  };


  class Plot : public QtWidget<SurfacePlot>
  {
  public:
      Plot();
  };


  Plot::Plot()
  {
    plot().setTitle("A Simple SurfacePlot Demonstration");
    
    Rosenbrock rosenbrock(this->plot());

    rosenbrock.setMesh(41,31);
    rosenbrock.setDomain(-1.73,1.5,-1.5,1.5);
    rosenbrock.setMinZ(-10);

    rosenbrock.create();

    plot().setRotation(30,0,15);
    plot().setScale(1,1,1);
    plot().setShift(0.15,0,0);
    plot().setZoom(0.9);

    for (unsigned i=0; i!=plot().coordinates()->axes.size(); ++i)
    {
      plot().coordinates()->axes[i].setMajors(7);
      plot().coordinates()->axes[i].setMinors(4);
    }


    plot().coordinates()->axes[X1].setLabelString("x-axis");
    plot().coordinates()->axes[Y1].setLabelString("y-axis");
    //coordinates()->axes[Z1].setLabelString(QChar(0x38f)); // Omega - see http://www.unicode.org/charts/


    plot().setCoordinateStyle(BOX);

    updateData();
  }

  int main(int argc, char **argv)
  {
      QApplication a(argc, argv);
      Plot plot;
      plot.resize(800,600);
      plot.show();
      return a.exec();
  }
