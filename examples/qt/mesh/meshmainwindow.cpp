#include <fstream>

#include <qmetaobject.h>
#include <qframe.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qfiledialog.h>       
#include <qstatusbar.h>
#include <qfileinfo.h>
#include <qslider.h>
#include <qtimer.h>
#include <qcombobox.h>
#include <qstring.h>
#include <qcheckbox.h>
#include <qcolordialog.h>
#include <qfontdialog.h>

//#include <protean3d/io.h>
//#include <protean3d/io_reader.h>

#include "meshmainwindow.h"

#include "functions.h"
#include "colormapreader.h"
#include "lightingdialog.h"

using namespace Protean3D;
using namespace std;

namespace
{
  Protean3D::RGBA Qt2GL(QColor col)
  {
    QRgb qrgb = col.rgb();
    RGBA rgba;
    rgba.r = qRed(qrgb) / 255.0;
    rgba.g = qGreen(qrgb) / 255.0;
    rgba.b = qBlue(qrgb) / 255.0;
    rgba.a = qAlpha(qrgb) / 255.0;
    return rgba;  
  }
}

MeshMainWindow::~MeshMainWindow()      
{
  delete widget_;
}

MeshMainWindow::MeshMainWindow( QWidget* parent )       
  : QMainWindow( parent )
{
  setupUi(this);

  QActionGroup* coord = new QActionGroup(this);
  coord->addAction(Box);
  coord->addAction(Frame);
  coord->addAction(None);
  //coord->setExclusive(true);

  grids_ = new QActionGroup(this);
  grids_->addAction(front); 
  grids_->addAction(back);
  grids_->addAction(right); 
  grids_->addAction(left);
  grids_->addAction(ceil);
  grids_->addAction(floor); 
  grids_->setExclusive(false);

  QActionGroup* plotstyle = new QActionGroup(this);
  plotstyle->addAction(pointstyle);
  plotstyle->addAction(wireframe);
  plotstyle->addAction(hiddenline);
  plotstyle->addAction(polygon);
  plotstyle->addAction(filledmesh);
  plotstyle->addAction(nodata);

  QActionGroup* floorstyle = new QActionGroup(this);
  floorstyle->addAction(floordata);
  floorstyle->addAction(flooriso);
  floorstyle->addAction(floornone);

  QActionGroup* color = new QActionGroup(this);
  color->addAction(axescolor);
  color->addAction(backgroundcolor);
  color->addAction(meshcolor);
  color->addAction(numbercolor);
  color->addAction(labelcolor);
  color->addAction(titlecolor);
  color->addAction(datacolor);
  color->addAction(resetcolor);

  QActionGroup* font = new QActionGroup(this);
  font->addAction(numberfont);
  font->addAction(labelfont);
  font->addAction(titlefont);
  font->addAction(resetfont);


  // toolbars

  QComboBox* functionCB = new QComboBox;
  QComboBox* psurfaceCB = new QComboBox;
  functionCB->clear();
  functionCB->addItem( tr( "---" ) );
  functionCB->addItem( tr( "Hat" ) );
  functionCB->addItem( tr( "Rosenbrock" ) );
  functionCB->addItem( tr( "Saddle" ) );
  functionCB->addItem( tr( "Sombrero" ) );
  functionCB->addItem( tr( "Ripple" ) );
  functionCB->setToolTip(tr( "Display function" ) );
  psurfaceCB->clear();
  psurfaceCB->addItem( tr( "---" ) );
  psurfaceCB->addItem( tr( "Torus" ) );
  psurfaceCB->addItem( tr( "Seashell" ) );
  psurfaceCB->addItem( tr( "Boy" ) );
  psurfaceCB->addItem( tr( "Dini" ) );
  psurfaceCB->setToolTip(tr( "Display parametric surface. Turn Lighting on for better quality."));
  mainToolbar->addWidget(functionCB);
  mainToolbar->addWidget(psurfaceCB);

  QObject::connect(Exit, SIGNAL(triggered()), SLOT(close()));

  QGridLayout *grid = new QGridLayout( frame );

  col_ = 0;
  legend_ = false;
  redraw_wait_ = 50;
  active_coordinate_system_ = None;

  widget_ = new QtWidget<SurfacePlot>(frame);
  grid->addWidget( widget_, 0, 0 );


  connect( coord, SIGNAL( triggered( QAction* ) ), this, SLOT( pickCoordSystem( QAction* ) ) );
  connect( plotstyle, SIGNAL( triggered( QAction* ) ), this, SLOT( pickPlotStyle( QAction* ) ) );
  connect( axescolor, SIGNAL( triggered() ), this, SLOT( pickAxesColor() ) );
  connect( backgroundcolor, SIGNAL( triggered() ), this, SLOT( pickBgColor() ) );
  connect( floorstyle, SIGNAL( triggered( QAction* ) ), this, SLOT( pickFloorStyle( QAction* ) ) );
  connect( meshcolor, SIGNAL( triggered() ), this, SLOT( pickMeshColor() ) );
  connect( numbercolor, SIGNAL( triggered() ), this, SLOT( pickNumberColor() ) );
  connect( labelcolor, SIGNAL( triggered() ), this, SLOT( pickLabelColor() ) );
  connect( titlecolor, SIGNAL( triggered() ), this, SLOT( pickTitleColor() ) );
  connect( datacolor, SIGNAL( triggered() ), this, SLOT( pickDataColor() ) );
  connect( lighting, SIGNAL( clicked() ), this, SLOT( pickLighting() ) );
  connect( resetcolor, SIGNAL( triggered() ), this, SLOT( resetColors() ) );
   connect( numberfont, SIGNAL( triggered() ), this, SLOT( pickNumberFont() ) );
  connect( labelfont, SIGNAL( triggered() ), this, SLOT( pickLabelFont() ) );
  connect( titlefont, SIGNAL( triggered() ), this, SLOT( pickTitleFont() ) );
  connect( resetfont, SIGNAL( triggered() ), this, SLOT( resetFonts() ) );
  connect( animation, SIGNAL( toggled(bool) ) , this, SLOT( toggleAnimation(bool) ) );
  connect( openFile, SIGNAL( triggered() ) , this, SLOT( open() ) );
  
  // only EXCLUSIVE groups emit selected :-/
  connect( left, SIGNAL( toggled( bool ) ), this, SLOT( setLeftGrid( bool ) ) );
  connect( right, SIGNAL( toggled( bool ) ), this, SLOT( setRightGrid( bool ) ) );
  connect( ceil, SIGNAL( toggled( bool ) ), this, SLOT( setCeilGrid( bool ) ) );
  connect( floor, SIGNAL( toggled( bool ) ), this, SLOT( setFloorGrid( bool ) ) );
  connect( back, SIGNAL( toggled( bool ) ), this, SLOT( setBackGrid( bool ) ) );
  connect( front, SIGNAL( toggled( bool ) ), this, SLOT( setFrontGrid( bool ) ) );

  timer_ = new QTimer( this );
  connect( timer_, SIGNAL(timeout()), this, SLOT(rotate()) );  
  connect( offsSlider, SIGNAL(valueChanged(int)), this, SLOT(setPolygonOffset(int)) );
  connect(normButton, SIGNAL(clicked()), this, SLOT(setStandardView()));  
  
  QString verstr(" protean3d ");
  verstr += QString::number(PROTEAN3D_MAJOR_VERSION) + ".";
  verstr += QString::number(PROTEAN3D_MINOR_VERSION) + ".";
  verstr += QString::number(PROTEAN3D_PATCH_VERSION) + " ";

  QLabel* info = new QLabel(verstr, statusBar());       
  statusBar()->addWidget(info, 0);
  filename_widget_ = new QLabel("                                  ", statusBar());
  statusBar()->addWidget(filename_widget_,0);
  dim_widget_ = new QLabel("", statusBar());
  statusBar()->addWidget(dim_widget_,0);
  rotate_label_ = new QLabel("", statusBar());
  statusBar()->addWidget(rotate_label_,0);
  shift_label_ = new QLabel("", statusBar());
  statusBar()->addWidget(shift_label_,0);
  scale_label_ = new QLabel("", statusBar());
  statusBar()->addWidget(scale_label_,0);
  zoom_label_ = new QLabel("", statusBar());
  statusBar()->addWidget(zoom_label_,0);
  
  connect(widget_, SIGNAL(rotationChanged(double,double,double)),this,SLOT(showRotate(double,double,double)));
  connect(widget_, SIGNAL(vieportShiftChanged(double,double)),this,SLOT(showShift(double,double)));
  connect(widget_, SIGNAL(scaleChanged(double,double,double)),this,SLOT(showScale(double,double,double)));
  connect(widget_, SIGNAL(zoomChanged(double)),this,SLOT(showZoom(double)));

  connect(functionCB, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(createFunction(const QString&)));
  connect(psurfaceCB, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(createPSurface(const QString&)));
  connect(projection, SIGNAL( toggled(bool) ), this, SLOT( toggleProjectionMode(bool)));
  connect(colorlegend, SIGNAL( toggled(bool) ), this, SLOT( toggleColorLegend(bool)));
  connect(autoscale, SIGNAL( toggled(bool) ), this, SLOT( toggleAutoScale(bool)));
  connect(shader, SIGNAL( toggled(bool) ), this, SLOT( toggleShader(bool)));
  connect(mouseinput, SIGNAL( toggled(bool) ), widget_, SLOT( enableMouse(bool)));
  connect(lightingswitch, SIGNAL( toggled(bool) ), this, SLOT( enableLighting(bool)));
  connect(normals, SIGNAL( toggled(bool) ), this, SLOT( showNormals(bool)));
  connect(normalsquality,  SIGNAL(valueChanged(int)), this, SLOT(setNormalQuality(int)) );
  connect(normalslength,  SIGNAL(valueChanged(int)), this, SLOT(setNormalLength(int)) );
      
  setStandardView();

  widget_->plot().coordinates()->setLineSmooth(true);
  widget_->plot().coordinates()->setGridLinesColor(RGBA(0.35,0.35,0.35,1));
  widget_->enableMouse(true);
  widget_->setKeySpeed(15,20,20);

  lightingdlg_ = new LightingDlg( this );
  lightingdlg_->assign( widget_);  

  widget_->plot().setTitleFont(QFont("Arial", 14, QFont::Normal));

  grids_->setEnabled(false);

  functionCB->setCurrentIndex(1);
  Box->setChecked(true);
  pickCoordSystem(Box);
}

void MeshMainWindow::open()
{
  QString s = QFileDialog::getOpenFileName( this, "", "../../data", "GridData Files (*.mes *.MES)");

  if ( s.isEmpty() || !widget_)
      return;
  
  QFileInfo fi( s );
  filename_widget_->setToolTip(s);
  QString ext = fi.suffix();
  filename_widget_->setText(fi.fileName());
    qApp->processEvents(); // enforces repaint;  
   
  for (unsigned i=0; i!=widget_->plot().coordinates()->axes.size(); ++i)
  {
    widget_->plot().coordinates()->axes[i].setMajors(4);
    widget_->plot().coordinates()->axes[i].setMinors(5);
    widget_->plot().coordinates()->axes[i].setLabelString("");
  }
  
  updateColorLegend(4,5);
  pickCoordSystem(active_coordinate_system_);
  widget_->plot().showColorLegend(legend_);
}

void MeshMainWindow::createFunction(QString const& name)
{
  widget_->makeCurrent();
  
  widget_->plot().legend()->setScale(LINEARSCALE);
  for (unsigned i=0; i!=widget_->plot().coordinates()->axes.size(); ++i)
  {
    widget_->plot().coordinates()->axes[i].setMajors(7);
    widget_->plot().coordinates()->axes[i].setMinors(5);
  }

  if (name == QString("Rosenbrock")) 
  {
    Rosenbrock rosenbrock(widget_->plot());
    
    rosenbrock.setMesh(50,51);
    rosenbrock.setDomain(-1.73,1.55,-1.5,1.95);
    rosenbrock.setMinZ(-100);
    
    rosenbrock.create();
    
    widget_->plot().coordinates()->axes[Z1].setScale(LOG10SCALE);
    widget_->plot().coordinates()->axes[Z2].setScale(LOG10SCALE);
    widget_->plot().coordinates()->axes[Z3].setScale(LOG10SCALE);
    widget_->plot().coordinates()->axes[Z4].setScale(LOG10SCALE);
    widget_->plot().legend()->setScale(LOG10SCALE);
  }
  else if (name == QString("Hat")) 
  {
    Hat hat(widget_->plot());
    
    hat.setMesh(51,72);
    hat.setDomain(-1.5,1.5,-1.5,1.5);
    hat.create();  
  }
  else if (name == QString("Ripple")) 
  {
    Ripple ripple(widget_->plot());
    ripple.setMesh(120,120);
    ripple.create();  
  }
  else if (name == QString("Saddle")) 
  {
    Saddle saddle;
    
    saddle.setMesh(71,71);
    double dom = 2.5;
    saddle.setDomain(-dom, dom, -dom, dom);
    saddle.assign(widget_->plot());
    saddle.create();
  }
  else if (name == QString("Sombrero")) 
  {
    Mex mex;
    
    mex.setMesh(91,91);
    double dom = 15;
    mex.setDomain(-dom, dom, -dom, dom);
    mex.create(widget_->plot());
  }

//  double a = widget_->plot().facets().first;
//  double b = widget_->plot().facets().second;
//
//  dim_widget_->setText(QString("Cells ") + QString::number(a*b) 
//    + " (" + QString::number(a) + "x" + QString::number(b) +")" );

  updateColorLegend(7,5);

  widget_->plot().coordinates()->axes[X1].setLabelString(QString("X1"));
  widget_->plot().coordinates()->axes[X2].setLabelString(QString("X2"));
  widget_->plot().coordinates()->axes[X3].setLabelString(QString("X3"));
  widget_->plot().coordinates()->axes[X4].setLabelString(QString("X4"));

  widget_->plot().coordinates()->axes[Y1].setLabelString(QString("Y1"));
  widget_->plot().coordinates()->axes[Y2].setLabelString(QString("Y2"));
  widget_->plot().coordinates()->axes[Y3].setLabelString(QString("Y3"));
  widget_->plot().coordinates()->axes[Y4].setLabelString(QString("Y4"));

  widget_->plot().coordinates()->axes[Z1].setLabelString(QString("Z1"));
  widget_->plot().coordinates()->axes[Z2].setLabelString(QString("Z2"));
  widget_->plot().coordinates()->axes[Z3].setLabelString(QString("Z3"));
  widget_->plot().coordinates()->axes[Z4].setLabelString(QString("Z4"));

  pickCoordSystem(active_coordinate_system_);
}

void MeshMainWindow::createPSurface(QString const& name)
{
  widget_->makeCurrent();
  if (name == QString("Torus")) 
  {
    Torus sf(widget_->plot());
    sf.create();
  }
  else if (name == QString("Seashell")) 
  {
    Seashell ss(widget_->plot());
    ss.create();
  }
  else if (name == QString("Boy")) 
  {
    Boy boy(widget_->plot());
    boy.create();
  }
  else if (name == QString("Dini")) 
  {
    Dini dini(widget_->plot());
    dini.create();
  }
  for (unsigned i=0; i!=widget_->plot().coordinates()->axes.size(); ++i)
  {
    widget_->plot().coordinates()->axes[i].setMajors(7);
    widget_->plot().coordinates()->axes[i].setMinors(5);
  }

//  double a = widget_->plot().facets().first;
//  double b = widget_->plot().facets().second;
//
//  dim_widget_->setText(QString("Cells ") + QString::number(a*b) 
//    + " (" + QString::number(a) + "x" + QString::number(b) +")" );

  updateColorLegend(7,5);

  widget_->plot().coordinates()->axes[X1].setLabelString(QString("X1"));
  widget_->plot().coordinates()->axes[X2].setLabelString(QString("X2"));
  widget_->plot().coordinates()->axes[X3].setLabelString(QString("X3"));
  widget_->plot().coordinates()->axes[X4].setLabelString(QString("X4"));

  widget_->plot().coordinates()->axes[Y1].setLabelString(QString("Y1"));
  widget_->plot().coordinates()->axes[Y2].setLabelString(QString("Y2"));
  widget_->plot().coordinates()->axes[Y3].setLabelString(QString("Y3"));
  widget_->plot().coordinates()->axes[Y4].setLabelString(QString("Y4"));

  widget_->plot().coordinates()->axes[Z1].setLabelString(QString("Z1"));
  widget_->plot().coordinates()->axes[Z2].setLabelString(QString("Z2"));
  widget_->plot().coordinates()->axes[Z3].setLabelString(QString("Z3"));
  widget_->plot().coordinates()->axes[Z4].setLabelString(QString("Z4"));

  pickCoordSystem(active_coordinate_system_);
}


void MeshMainWindow::pickCoordSystem( QAction* action)
{
  if (!action || !widget_)
    return;

  active_coordinate_system_ = action;
  
  widget_->plot().setTitle("Protean3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");

  if (!widget_->plot().hasData())
  {
    double l = 0.6;
    widget_->plot().createCoordinateSystem(Triple(-l,-l,-l), Triple(l,l,l));
    for (unsigned i=0; i!=widget_->plot().coordinates()->axes.size(); ++i)
    {
      widget_->plot().coordinates()->axes[i].setMajors(4);
      widget_->plot().coordinates()->axes[i].setMinors(5);
    }
  }      

  if (action == Box || action == Frame)
  {
    if (action == Box)
      widget_->plot().setCoordinateStyle(BOX);
    if (action == Frame)
      widget_->plot().setCoordinateStyle(FRAME);

    widget_->updateGL();
    grids_->setEnabled(true);
  }
  else if (action == None)
  {
    widget_->plot().setTitle("Protean3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");
    widget_->plot().setCoordinateStyle(NOCOORD);

    widget_->updateGL();
    grids_->setEnabled(false);
  }
}

void MeshMainWindow::pickPlotStyle( QAction* action )
{
  if (!action || !widget_)
    return;

  if (action == polygon)
  {
    widget_->plot().setPlotStyle(FILLED);
  }
  else if (action == filledmesh)
  {
    widget_->plot().setPlotStyle(FILLEDMESH);
  }
  else if (action == wireframe)
  {
    widget_->plot().setPlotStyle(WIREFRAME);
  }
  else if (action == hiddenline)
  {
    widget_->plot().setPlotStyle(HIDDENLINE);
  }
  else if (action == pointstyle)
  {
    widget_->plot().setPlotStyle(Protean3D::POINTS);
  }
  else
  {
    widget_->plot().setPlotStyle(NOPLOT);
  }
  widget_->updateData();
}

void
MeshMainWindow::pickFloorStyle( QAction* action )
{
  if (!action || !widget_)
    return;

  if (action == floordata)
  {
    widget_->plot().setFloorStyle(FLOORDATA);
  }
  else if (action == flooriso)
  {
    widget_->plot().setFloorStyle(FLOORISO);
  }
  else
  {
    widget_->plot().setFloorStyle(NOFLOOR);
  }
  
  widget_->updateData();
}  

void MeshMainWindow::setLeftGrid(bool b)
{
  setGrid(Protean3D::LEFT,b);
}
void MeshMainWindow::setRightGrid(bool b)
{
  setGrid(Protean3D::RIGHT,b);
}
void MeshMainWindow::setCeilGrid(bool b)
{
  setGrid(Protean3D::CEIL,b);
}
void MeshMainWindow::setFloorGrid(bool b)
{
  setGrid(Protean3D::FLOOR,b);
}
void MeshMainWindow::setFrontGrid(bool b)
{
  setGrid(Protean3D::FRONT,b);
}
void MeshMainWindow::setBackGrid(bool b)
{
  setGrid(Protean3D::BACK,b);
}

void MeshMainWindow::setGrid(Protean3D::SIDE s, bool b)
{
  if (!widget_)
    return;
  
 int sum = widget_->plot().coordinates()->grids();

  if (b)
    sum |= s;
  else
    sum &= ~s;

  widget_->plot().coordinates()->setGridLines(sum!=Protean3D::NOSIDEGRID, sum!=Protean3D::NOSIDEGRID, sum);
  widget_->updateGL();
}

void MeshMainWindow::resetColors()
{
  if (!widget_)
    return;

  const RGBA axc = RGBA(0,0,0,1);
  const RGBA bgc = RGBA(1.0,1.0,1.0,1.0);
  const RGBA msc = RGBA(0,0,0,1);
  const RGBA nuc = RGBA(0,0,0,1);
  const RGBA lbc = RGBA(0,0,0,1);
  const RGBA tc = RGBA(0,0,0,1);

  widget_->plot().coordinates()->setAxesColor(axc);
  widget_->plot().setBackgroundColor(bgc);
  widget_->plot().setMeshColor(msc);
  widget_->updateData();
  widget_->plot().coordinates()->setNumberColor(nuc);
  widget_->plot().coordinates()->setLabelColor(lbc);
  widget_->plot().setTitleColor(tc);

  widget_->plot().setDataColor(std::shared_ptr<Color>(new StandardColor()));
  widget_->updateData();  
  widget_->plot().updateNormals();
  widget_->updateGL();
}


void MeshMainWindow::pickAxesColor()
{
  
  QColor c = QColorDialog::getColor( Qt::white, this );
  if ( !c.isValid() )
    return;
  RGBA rgb = Qt2GL(c);
  widget_->plot().coordinates()->setAxesColor(rgb);
  widget_->updateGL();
}

void MeshMainWindow::pickBgColor()
{
  
  QColor c = QColorDialog::getColor( Qt::white, this );
  if ( !c.isValid() )
    return;
  RGBA rgb = Qt2GL(c);
  widget_->plot().setBackgroundColor(rgb);
  widget_->updateGL();
}

void MeshMainWindow::pickMeshColor()
{
  
  QColor c = QColorDialog::getColor( Qt::white, this );
  if ( !c.isValid() )
    return;
  RGBA rgb = Qt2GL(c);
  widget_->plot().setMeshColor(rgb);
  widget_->updateData();
}

void MeshMainWindow::pickNumberColor()
{
  
  QColor c = QColorDialog::getColor( Qt::white, this );
  if ( !c.isValid() )
    return;
  RGBA rgb = Qt2GL(c);
  widget_->plot().coordinates()->setNumberColor(rgb);
  widget_->updateGL();
}

void MeshMainWindow::pickLabelColor()
{
   QColor c = QColorDialog::getColor( Qt::white, this );
  if ( !c.isValid() )
    return;
  RGBA rgb = Qt2GL(c);
  widget_->plot().coordinates()->setLabelColor(rgb);
  widget_->updateGL();
}
void MeshMainWindow::pickTitleColor()
{
   QColor c = QColorDialog::getColor( Qt::white, this );
  if ( !c.isValid() )
    return;
  RGBA rgb = Qt2GL(c);
  widget_->plot().setTitleColor(rgb);
  widget_->updateGL();
}

void MeshMainWindow::pickLighting()
{
  lightingdlg_->show();
}

void MeshMainWindow::pickDataColor()
{
  QString s =  QFileDialog::getOpenFileName( this, "", "./../colormaps", "Colormap files (*.map *.MAP)");
  adaptDataColors(s);
}

void MeshMainWindow::adaptDataColors(const QString& fileName)
{
  ColorVector cv;
  
  if (!openColorMap(cv, fileName))
    return;
  
  std::shared_ptr<StandardColor> col_(new StandardColor());
  col_->setColorVector(cv);
  
  widget_->plot().setDataColor(col_);
  widget_->updateData();
  widget_->plot().updateNormals();
  widget_->plot().showColorLegend(legend_);
  widget_->updateGL();
}

void MeshMainWindow::pickNumberFont()
{
  bool ok;
  QFont font = QFontDialog::getFont(&ok, this );
  if ( !ok ) 
  {
    return;
  } 
  widget_->plot().coordinates()->setNumberFont(font);
  widget_->updateGL();
}
void MeshMainWindow::pickLabelFont()
{
  bool ok;
  QFont font = QFontDialog::getFont(&ok, this );
  if ( !ok ) 
  {
    return;
  } 
  widget_->plot().coordinates()->setLabelFont(font);
  widget_->updateGL();
}
void MeshMainWindow::pickTitleFont()
{
  bool ok;
  QFont font = QFontDialog::getFont(&ok, this );
  if ( !ok ) 
  {
    return;
  } 
  widget_->plot().setTitleFont(font);
}

void MeshMainWindow::resetFonts()
{
  widget_->plot().coordinates()->setNumberFont(QFont("Courier", 12));
  widget_->plot().coordinates()->setLabelFont(QFont("Courier", 14, QFont::Bold));
  widget_->plot().setTitleFont(QFont("Arial", 14, QFont::Normal));
  widget_->updateGL();
}

void MeshMainWindow::setStandardView()
{
  widget_->plot().setRotation(30,0,15);
  widget_->plot().setViewportShift(0.05,0);
  widget_->plot().setScale(1,1,1);
  widget_->plot().setZoom(0.95);
}

/*!
  Turns animation on or off
*/
void MeshMainWindow::toggleAnimation(bool val)
{
  if ( val )
  {
    timer_->start( redraw_wait_ ); // Wait this many msecs before redraw
  }
  else
  {
    timer_->stop();
  }
}

void MeshMainWindow::rotate()
{
  if (!widget_)
    return;

  widget_->plot().setRotation(
    int(widget_->plot().xRotation() + 1) % 360,
    int(widget_->plot().yRotation() + 1) % 360,
    int(widget_->plot().zRotation() + 1) % 360
    );
  widget_->updateGL();
}

void
MeshMainWindow::toggleProjectionMode(bool val)
{
  widget_->plot().setOrtho(val);
}

void
MeshMainWindow::toggleColorLegend(bool val)
{
  legend_ = val;
  widget_->plot().showColorLegend(val);
}

void
MeshMainWindow::toggleAutoScale(bool val)
{
  widget_->plot().coordinates()->setAutoScale(val);
  widget_->updateGL();
}

void
MeshMainWindow::toggleShader(bool val)
{
  if (val)
    widget_->plot().setShading(GOURAUD);
  else
    widget_->plot().setShading(FLAT);
}

void
MeshMainWindow::setPolygonOffset(int val)
{
  widget_->plot().setPolygonOffset(val / 10.0);
  widget_->updateData();
}

void
MeshMainWindow::showRotate(double x, double y, double z)    
{
  rotate_label_->setText(" Angles ("  + QString::number(x,'g',3) + " ," 
                                  + QString::number(y,'g',3) + " ,"
                                  + QString::number(z,'g',3) + ")");
}
void
MeshMainWindow::showShift(double x, double y)    
{
  shift_label_->setText(" Shifts (" + QString::number(x,'g',3) + " ," 
                                  + QString::number(y,'g',3) + " )"
                                  );
}
void
MeshMainWindow::showScale(double x, double y, double z)    
{
  scale_label_->setText(" Scales (" + QString::number(x,'g',3) + " ," 
                                  + QString::number(y,'g',3) + " ,"
                                  + QString::number(z,'g',3) + ")");
}
void
MeshMainWindow::showZoom(double z)    
{
  zoom_label_->setText(" Zoom "  + QString::number(z,'g',3)); 
}

void
MeshMainWindow::showNormals(bool val)
{
  widget_->plot().showNormals(val);
  widget_->plot().updateNormals();
  widget_->updateGL();
}

void
MeshMainWindow::setNormalLength(int val)
{
  widget_->plot().setNormalLength(val / 400.);
  widget_->plot().updateNormals();
  widget_->updateGL();
}

void
MeshMainWindow::setNormalQuality(int val)
{
  widget_->plot().setNormalQuality(val);
  widget_->plot().updateNormals();
  widget_->updateGL();
}

bool
MeshMainWindow::openColorMap(ColorVector& cv, QString fname)
{  
  if (fname.isEmpty())
    return false;
  
  ifstream file(fname.toLocal8Bit().constData());

  if (!file)
    return false;
  
  RGBA rgb;
  cv.clear();
  
  while ( file ) 
  {    
    file >> rgb.r >> rgb.g >> rgb.b;
    file.ignore(1000,'\n');
    if (!file.good())
      break;
    else
    {
      rgb.a = 1;
      rgb.r /= 255;
      rgb.g /= 255;
      rgb.b /= 255;
      cv.push_back(rgb);  
    }
  }

  return true;
}

void 
MeshMainWindow::updateColorLegend(int majors, int minors)
{
  widget_->plot().legend()->setMajors(majors);
  widget_->plot().legend()->setMinors(minors);
  double start, stop;
  widget_->plot().coordinates()->axes[Z1].limits(start,stop);
  widget_->plot().legend()->setLimits(start, stop);
}    

void MeshMainWindow::enableLighting(bool val)
{
  widget_->plot().enableLighting(val);
  widget_->plot().illuminate(0);
  widget_->updateGL();
}
