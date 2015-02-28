//#include <qlayout.h>
//#include <qframe.h>
//#include <qslider.h>
//#include <qcheckbox.h>
//#include <qpushbutton.h>
//
//#include "lightingdialog.h"
//
//using namespace std;
//using namespace Traits3D;
//
//class Sphere : public ParametricSurface
//{
//public:
//
//  Sphere(SurfacePlot& pw)
//  :ParametricSurface(pw)
//  {
//    setMesh(41,31);
//    setDomain(0,2*Traits3D::PI,0,Traits3D::PI);
//    setPeriodic(false,false);
//  }
//
//
//  Triple operator()(double u, double v)
//  {
//    double x,y,z;
//    double r = 1;
//    x = r*cos(u)*sin(v);
//    y = r*sin(u)*sin(v);
//    z = r*cos(v);
//    return Triple(x,y,z);
//  }
//};
//
//
///////////////////////////////////////////////////////////////////
////
////   Plot
////
///////////////////////////////////////////////////////////////////
//
//Plot::Plot(QWidget *parent)
//: QtWidget<SurfacePlot>(parent)
//{
//  plot().setTitle("A Simple SurfacePlot Demonstration");
//  
//  Sphere sphere(this->plot());
//  sphere.create();
//
//  reset();  
//  assignMouse(Qt::LeftButton,
//    Qt::RightButton,
//    Qt::LeftButton,
//    Qt::NoButton,
//    Qt::NoButton,
//    Qt::NoButton,
//    Qt::NoButton,
//    Qt::NoButton,
//    Qt::NoButton
//    );
//
//  stick = plot().addEnrichment(std::shared_ptr<Enrichment>(new Pointer(0.05)));
//  safe_down_cast<Pointer>(stick)->setPos(0,0,1);
//}
//
//void Plot::reset()
//{
//  makeCurrent();
//  plot().setRotation(0,0,0);
//  plot().setTitle("Use your mouse buttons and keyboard");
//  plot().setTitleFont(QFont("Arial", 8, QFont::Bold));
//  plot().setTitleColor(Traits3D::Color(0.9,0.9,0.9));
//  plot().setSmoothMesh(true);
//  plot().setZoom(0.9);
//  plot().setCoordinateStyle(NOCOORD);
//  plot().setMeshColor(Traits3D::Color(0.6,0.6,0.6,0.3));
//  plot().setPlotStyle(FILLEDMESH);
//  plot().setBackgroundColor(Traits3D::Color(0,0,0));
//
//  updateData();
//}
//
///////////////////////////////////////////////////////////////////
////
////   Pointer
////
///////////////////////////////////////////////////////////////////
//
//
//Pointer::Pointer(double rad)
//{
//  configure(rad);
//}
//
//void Pointer::configure(double rad)
//{
//  plot_p = 0;
//  radius_ = rad;
//}
//
//void Pointer::draw()
//{
//  GLint mode;
//  glGetIntegerv(GL_MATRIX_MODE, &mode);
//  glMatrixMode( GL_MODELVIEW );
//  glPushMatrix();
//  
//  glColor3d(1,0,0);
//  glBegin(GL_LINES);
//    glVertex3d(pos_.x, pos_.y, pos_.z);
//    glVertex3d(0, 0, 0);
//  glEnd();
//
//  glPopMatrix();
//  glMatrixMode(mode);
//}
//
//
//LightingDlg::LightingDlg(QWidget *parent)
//:QDialog(parent)
//{
//  setupUi(this);
//  QGridLayout *grid = new QGridLayout( frame);
//
//  data_plot_ = 0;
//  
//  plot_ = new Plot(frame);
//  plot_->updateData();
//
//  grid->addWidget( plot_, 0, 0 );
//
//  connect( stdlight, SIGNAL( clicked() ), this, SLOT( reset() ) );
//  connect( distSL, SIGNAL(valueChanged(int)), this, SLOT(setDistance(int)) );
//  connect( emissSL, SIGNAL(valueChanged(int)), this, SLOT(setEmission(int)) );
//  connect( ambdiffSL, SIGNAL(valueChanged(int)), this, SLOT(setDiff(int)) );
//  connect( specSL, SIGNAL(valueChanged(int)), this, SLOT(setSpec(int)) );
//  connect( shinSL, SIGNAL(valueChanged(int)), this, SLOT(setShin(int)) );
//  connect( plot_, SIGNAL(rotationChanged(double, double, double)), this, SLOT(setRotation(double, double, double)) );
//}
//
//LightingDlg::~LightingDlg()
//{
//  delete plot_;
//}
//
//void LightingDlg::setEmission(int val)
//{
//  if (!data_plot_)
//    return;
//  data_plot_->plot().setMaterialComponent(GL_EMISSION, val / 100.);
//  data_plot_->updateGL();
//}
//void LightingDlg::setDiff(int val)
//{
//  if (!data_plot_)
//    return;
//  data_plot_->plot().setLightComponent(GL_DIFFUSE, val / 100.);
//  data_plot_->updateGL();
//}
//void LightingDlg::setSpec(int val)
//{
//  if (!data_plot_)
//    return;
//  data_plot_->plot().setMaterialComponent(GL_SPECULAR, val / 100.);
//  data_plot_->updateGL();
//}
//void LightingDlg::setShin(int val)
//{
//  if (!data_plot_)
//    return;
//  data_plot_->plot().setShininess( val / 100.);
//  data_plot_->updateGL();
//}
//
//void LightingDlg::reset()
//{
//  plot_->reset();
//  if (data_plot_)
//    data_plot_->updateGL();
//}
//
//void LightingDlg::setDistance(int val)
//{
//  
//  safe_down_cast<Pointer>(plot_->stick)->setPos(0,0,val/100.);
//  plot_->updateData();
//  
//  double drad = (data_plot_->plot().hull().maxVertex-data_plot_->plot().hull().minVertex).length();
//  drad *= val/20.;
//
//  data_plot_->plot().setLightShift(drad,drad,drad);
//  data_plot_->updateGL();
//}
//
//void LightingDlg::assign(Traits3D::QtWidget<Traits3D::SurfacePlot>* pl) 
//{
//  if (!pl) 
//    return;
//  data_plot_ = pl;
//}
//
//void LightingDlg::setRotation(double x, double y, double z)
//{
//  if (!data_plot_)
//    return;
//  
//  setDistance(distSL->value());
//  data_plot_->plot().setLightRotation(x,y,z);
//  data_plot_->updateGL();
//}
