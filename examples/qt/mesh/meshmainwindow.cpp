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

//#include "traits3d/io.h"
//#include "traits3d/io_reader.h"

#include "meshmainwindow.h"

#include "functions.h"
#include "colormapreader.h"
#include "lightingdialog.h"

using namespace traits3d;
using namespace std;

using namespace traits3d;

namespace
{
Color Qt2GL(QColor col)
{
    QRgb qrgb = col.rgb();
    Color rgba;
    rgba.r = qRed(qrgb) / 255.0f;
    rgba.g = qGreen(qrgb) / 255.0f;
    rgba.b = qBlue(qrgb) / 255.0f;
    rgba.a = qAlpha(qrgb) / 255.0f;
    return rgba;
}
}

MeshMainWindow::~MeshMainWindow()
{
    delete widget_;
}

MeshMainWindow::MeshMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    QActionGroup *coord = new QActionGroup(this);
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
    QActionGroup *plotstyle = new QActionGroup(this);
    plotstyle->addAction(pointstyle);
    plotstyle->addAction(wireframe);
    plotstyle->addAction(hiddenline);
    plotstyle->addAction(polygon);
    plotstyle->addAction(filledmesh);
    plotstyle->addAction(nodata);
    QActionGroup *floorstyle = new QActionGroup(this);
    floorstyle->addAction(floordata);
    floorstyle->addAction(flooriso);
    floorstyle->addAction(floornone);
    QActionGroup *color = new QActionGroup(this);
    color->addAction(axescolor);
    color->addAction(backgroundcolor);
    color->addAction(meshcolor);
    color->addAction(numbercolor);
    color->addAction(labelcolor);
    color->addAction(titlecolor);
    color->addAction(datacolor);
    color->addAction(resetcolor);
    QActionGroup *font = new QActionGroup(this);
    font->addAction(numberfont);
    font->addAction(labelfont);
    font->addAction(titlefont);
    font->addAction(resetfont);
    // toolbars
    QComboBox *functionCB = new QComboBox;
    QComboBox *psurfaceCB = new QComboBox;
    functionCB->clear();
    functionCB->addItem(tr("---"));
    functionCB->addItem(tr("Hat"));
    functionCB->addItem(tr("Rosenbrock"));
    functionCB->addItem(tr("Saddle"));
    functionCB->addItem(tr("Sombrero"));
    functionCB->addItem(tr("Ripple"));
    functionCB->setToolTip(tr("Display function"));
    psurfaceCB->clear();
    psurfaceCB->addItem(tr("---"));
    psurfaceCB->addItem(tr("Torus"));
    psurfaceCB->addItem(tr("Seashell"));
    psurfaceCB->addItem(tr("Boy"));
    psurfaceCB->addItem(tr("Dini"));
    psurfaceCB->setToolTip(tr("Display parametric surface. Turn Lighting on for better quality."));
    mainToolbar->addWidget(functionCB);
    mainToolbar->addWidget(psurfaceCB);
    QObject::connect(Exit, SIGNAL(triggered()), SLOT(close()));
    QGridLayout *grid = new QGridLayout(frame);
    legend_ = false;
    redraw_wait_ = 50;
    active_coordinate_system_ = None;
    widget_ = new QtWidget<SurfacePlot>(frame);
    grid->addWidget(widget_, 0, 0);
    connect(coord, SIGNAL(triggered(QAction *)), this, SLOT(pickCoordSystem(QAction *)));
    connect(plotstyle, SIGNAL(triggered(QAction *)), this, SLOT(pickPlotStyle(QAction *)));
    connect(axescolor, SIGNAL(triggered()), this, SLOT(pickAxesColor()));
    connect(backgroundcolor, SIGNAL(triggered()), this, SLOT(pickBgColor()));
    connect(floorstyle, SIGNAL(triggered(QAction *)), this, SLOT(pickFloorStyle(QAction *)));
    connect(meshcolor, SIGNAL(triggered()), this, SLOT(pickMeshColor()));
    connect(numbercolor, SIGNAL(triggered()), this, SLOT(pickNumberColor()));
    connect(labelcolor, SIGNAL(triggered()), this, SLOT(pickLabelColor()));
    connect(titlecolor, SIGNAL(triggered()), this, SLOT(pickTitleColor()));
    connect(datacolor, SIGNAL(triggered()), this, SLOT(pickDataColor()));
    connect(lighting, SIGNAL(clicked()), this, SLOT(pickLighting()));
    connect(resetcolor, SIGNAL(triggered()), this, SLOT(resetColors()));
    connect(numberfont, SIGNAL(triggered()), this, SLOT(pickNumberFont()));
    connect(labelfont, SIGNAL(triggered()), this, SLOT(pickLabelFont()));
    connect(titlefont, SIGNAL(triggered()), this, SLOT(pickTitleFont()));
    connect(resetfont, SIGNAL(triggered()), this, SLOT(resetFonts()));
    connect(animation, SIGNAL(toggled(bool)) , this, SLOT(toggleAnimation(bool)));
    connect(openFile, SIGNAL(triggered()) , this, SLOT(open()));
    // only EXCLUSIVE groups emit selected :-/
    connect(left, SIGNAL(toggled(bool)), this, SLOT(setLeftGrid(bool)));
    connect(right, SIGNAL(toggled(bool)), this, SLOT(setRightGrid(bool)));
    connect(ceil, SIGNAL(toggled(bool)), this, SLOT(setCeilGrid(bool)));
    connect(floor, SIGNAL(toggled(bool)), this, SLOT(setFloorGrid(bool)));
    connect(back, SIGNAL(toggled(bool)), this, SLOT(setBackGrid(bool)));
    connect(front, SIGNAL(toggled(bool)), this, SLOT(setFrontGrid(bool)));
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(rotate()));
    connect(offsSlider, SIGNAL(valueChanged(int)), this, SLOT(setPolygonOffset(int)));
    connect(normButton, SIGNAL(clicked()), this, SLOT(setStandardView()));
    QString verstr(" traits3d ");
    verstr += QString::number(TRAITS3D_MAJOR_VERSION) + ".";
    verstr += QString::number(TRAITS3D_MINOR_VERSION) + ".";
    verstr += QString::number(TRAITS3D_PATCH_VERSION) + " ";
    QLabel *info = new QLabel(verstr, statusBar());
    statusBar()->addWidget(info, 0);
    filename_widget_ = new QLabel("                                  ", statusBar());
    statusBar()->addWidget(filename_widget_, 0);
    dim_widget_ = new QLabel("", statusBar());
    statusBar()->addWidget(dim_widget_, 0);
    rotate_label_ = new QLabel("", statusBar());
    statusBar()->addWidget(rotate_label_, 0);
    shift_label_ = new QLabel("", statusBar());
    statusBar()->addWidget(shift_label_, 0);
    scale_label_ = new QLabel("", statusBar());
    statusBar()->addWidget(scale_label_, 0);
    zoom_label_ = new QLabel("", statusBar());
    statusBar()->addWidget(zoom_label_, 0);
    connect(widget_, SIGNAL(rotationChanged(double, double, double)), this, SLOT(showRotate(double, double, double)));
    connect(widget_, SIGNAL(vieportShiftChanged(double, double)), this, SLOT(showShift(double, double)));
    connect(widget_, SIGNAL(scaleChanged(double, double, double)), this, SLOT(showScale(double, double, double)));
    connect(widget_, SIGNAL(zoomChanged(double)), this, SLOT(showZoom(double)));
    connect(functionCB, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(createFunction(const QString &)));
    connect(psurfaceCB, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(createPSurface(const QString &)));
    connect(projection, SIGNAL(toggled(bool)), this, SLOT(toggleProjectionMode(bool)));
    connect(colorlegend, SIGNAL(toggled(bool)), this, SLOT(toggleColorLegend(bool)));
    connect(autoscale, SIGNAL(toggled(bool)), this, SLOT(toggleAutoScale(bool)));
    connect(shader, SIGNAL(toggled(bool)), this, SLOT(toggleShader(bool)));
    connect(mouseinput, SIGNAL(toggled(bool)), widget_, SLOT(enableMouse(bool)));
    connect(lightingswitch, SIGNAL(toggled(bool)), this, SLOT(enableLighting(bool)));
    connect(normals, SIGNAL(toggled(bool)), this, SLOT(showNormals(bool)));
    connect(normalsquality,  SIGNAL(valueChanged(int)), this, SLOT(setNormalQuality(int)));
    connect(normalslength,  SIGNAL(valueChanged(int)), this, SLOT(setNormalLength(int)));
    setStandardView();
    widget_->plot3d->coordinates()->setGridLineColor(Color(0.5, 0.5, 0.5, 1));
    widget_->enableMouse(true);
    widget_->setKeySpeed(15, 20, 20);
    //  lightingdlg_ = new LightingDlg( this );
    //  lightingdlg_->assign( widget_);
    //  widget_->plot3d->setTitleFont(QFont("Arial", 14, QFont::Normal));
    grids_->setEnabled(false);
    //functionCB->setCurrentIndex(1);
    Box->setChecked(true);
    pickCoordSystem(Box);
}

void MeshMainWindow::open()
{
    QString s = QFileDialog::getOpenFileName(this, "", "../../data", "GridData Files (*.mes *.MES)");

    if (s.isEmpty() || !widget_)
        return;

    QFileInfo fi(s);
    filename_widget_->setToolTip(s);
    QString ext = fi.suffix();
    filename_widget_->setText(fi.fileName());
    qApp->processEvents(); // enforces repaint;

    for (unsigned i = 0; i != widget_->plot3d->coordinates()->axes.size(); ++i)
    {
        widget_->plot3d->coordinates()->axes[i].setMajors(4);
        widget_->plot3d->coordinates()->axes[i].setMinors(5);
        widget_->plot3d->coordinates()->axes[i].setLabelText("");
    }

    updateColorLegend(4, 5);
    pickCoordSystem(active_coordinate_system_);
    //  widget_->plot3d->showColorLegend(legend_);
}

void MeshMainWindow::createFunction(QString const &name)
{
    widget_->makeCurrent();

    //widget_->plot3d->legend()->setScale(LINEARSCALE);
    for (unsigned i = 0; i != widget_->plot3d->coordinates()->axes.size(); ++i)
    {
        widget_->plot3d->coordinates()->axes[i].setMajors(7);
        widget_->plot3d->coordinates()->axes[i].setMinors(5);
    }

    std::shared_ptr<Function> function;

    if (name == QString("Rosenbrock"))
    {
        function = std::make_shared<Rosenbrock>();
        function->setDomainResolution(50, 51);
        function->setDomain(-2.73, 1.55, -1.5, 2.15);
        function->setRange(-100, 1000);
        widget_->plot3d->coordinates()->axes[Z1].setScale(LOG10SCALE);
        widget_->plot3d->coordinates()->axes[Z2].setScale(LOG10SCALE);
        widget_->plot3d->coordinates()->axes[Z3].setScale(LOG10SCALE);
        widget_->plot3d->coordinates()->axes[Z4].setScale(LOG10SCALE);
        //widget_->plot3d->legend()->setScale(LOG10SCALE);
    }
    else if (name == QString("Hat"))
    {
        function = std::make_shared<Hat>();
        function->setDomainResolution(51, 72);
        function->setDomain(-1.5, 1.5, -1.5, 1.5);
    }
    else if (name == QString("Ripple"))
    {
        function = std::make_shared<Ripple>();
        function->setDomainResolution(120, 120);
    }
    else if (name == QString("Saddle"))
    {
        function = std::make_shared<Saddle>();
        function->setDomainResolution(71, 71);
        double dom = 2.5;
        function->setDomain(-dom, dom, -dom, dom);
    }
    else if (name == QString("Sombrero"))
    {
        function = std::make_shared<Mex>();
        function->setDomainResolution(91, 91);
        double dom = 15;
        function->setDomain(-dom, dom, -dom, dom);
    }

    if (function.get() != nullptr)
    {
        widget_->plot3d->addPositionData(function->dataF());
        resetColors();
    }

    //  double a = widget_->plot3d->facets().first;
    //  double b = widget_->plot3d->facets().second;
    //
    //  dim_widget_->setText(QString("Cells ") + QString::number(a*b)
    //    + " (" + QString::number(a) + "x" + QString::number(b) +")" );
    updateColorLegend(7, 5);
    widget_->plot3d->coordinates()->axes[X1].setLabelText("X1");
    widget_->plot3d->coordinates()->axes[X2].setLabelText("X2");
    widget_->plot3d->coordinates()->axes[X3].setLabelText("X3");
    widget_->plot3d->coordinates()->axes[X4].setLabelText("X4");
    widget_->plot3d->coordinates()->axes[Y1].setLabelText("Y1");
    widget_->plot3d->coordinates()->axes[Y2].setLabelText("Y2");
    widget_->plot3d->coordinates()->axes[Y3].setLabelText("Y3");
    widget_->plot3d->coordinates()->axes[Y4].setLabelText("Y4");
    widget_->plot3d->coordinates()->axes[Z1].setLabelText("Z1");
    widget_->plot3d->coordinates()->axes[Z2].setLabelText("Z2");
    widget_->plot3d->coordinates()->axes[Z3].setLabelText("Z3");
    widget_->plot3d->coordinates()->axes[Z4].setLabelText("Z4");
    pickCoordSystem(active_coordinate_system_);
}

void MeshMainWindow::createPSurface(QString const &name)
{
    widget_->makeCurrent();
    std::shared_ptr<ParametricSurface> surface;

    if (name == QString("Torus"))
        surface = std::make_shared<Torus>();
    else if (name == QString("Seashell"))
        surface = std::make_shared<Seashell>();
    else if (name == QString("Boy"))
        surface = std::make_shared<Boy>();
    else if (name == QString("Dini"))
        surface = std::make_shared<Dini>();

    for (unsigned i = 0; i != widget_->plot3d->coordinates()->axes.size(); ++i)
    {
        widget_->plot3d->coordinates()->axes[i].setMajors(7);
        widget_->plot3d->coordinates()->axes[i].setMinors(5);
    }

    if (surface.get() != nullptr)
    {
        std::vector<TripleF> data = convert(surface->data());
        widget_->plot3d->addPositionData(data, surface->uSize(), surface->vSize());
        resetColors();
    }

    //  double a = widget_->plot3d->facets().first;
    //  double b = widget_->plot3d->facets().second;
    //
    //  dim_widget_->setText(QString("Cells ") + QString::number(a*b)
    //    + " (" + QString::number(a) + "x" + QString::number(b) +")" );
    updateColorLegend(7, 5);
    widget_->plot3d->coordinates()->axes[X1].setLabelText("X1");
    widget_->plot3d->coordinates()->axes[X2].setLabelText("X2");
    widget_->plot3d->coordinates()->axes[X3].setLabelText("X3");
    widget_->plot3d->coordinates()->axes[X4].setLabelText("X4");
    widget_->plot3d->coordinates()->axes[Y1].setLabelText("Y1");
    widget_->plot3d->coordinates()->axes[Y2].setLabelText("Y2");
    widget_->plot3d->coordinates()->axes[Y3].setLabelText("Y3");
    widget_->plot3d->coordinates()->axes[Y4].setLabelText("Y4");
    widget_->plot3d->coordinates()->axes[Z1].setLabelText("Z1");
    widget_->plot3d->coordinates()->axes[Z2].setLabelText("Z2");
    widget_->plot3d->coordinates()->axes[Z3].setLabelText("Z3");
    widget_->plot3d->coordinates()->axes[Z4].setLabelText("Z4");
    pickCoordSystem(active_coordinate_system_);
}


void MeshMainWindow::pickCoordSystem(QAction *action)
{
    if (!action || !widget_)
        return;

    active_coordinate_system_ = action;
    widget_->plot3d->setTitle("Traits3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");

    //if (!widget_->plot3d->hasData())
    //{
    //  double l = 0.6;
    //  widget_->plot3d->createCoordinateSystem(Triple(-l, -l, -l), Triple(l, l, l));
    //  for (unsigned i = 0; i != widget_->plot3d->coordinates()->axes.size(); ++i)
    //  {
    //    widget_->plot3d->coordinates()->axes[i].setMajors(4);
    //    widget_->plot3d->coordinates()->axes[i].setMinors(5);
    //  }
    //}

    if (action == Box || action == Frame)
    {
        if (action == Box)
            widget_->plot3d->setCoordinateStyle(BOX);

        if (action == Frame)
            widget_->plot3d->setCoordinateStyle(FRAME);

        widget_->update();
        grids_->setEnabled(true);
    }
    else if (action == None)
    {
        widget_->plot3d->setTitle("Traits3D (Use Ctrl-Alt-Shift-LeftBtn-Wheel or keyboard)");
        widget_->plot3d->setCoordinateStyle(NOCOORDINATES);
        widget_->update();
        grids_->setEnabled(false);
    }
}

void MeshMainWindow::pickPlotStyle(QAction *action)
{
    //if (!action || !widget_)
    //  return;
    //if (action == polygon)
    //{
    //  widget_->plot3d->setPlotStyle(FILLED);
    //}
    //else if (action == filledmesh)
    //{
    //  widget_->plot3d->setPlotStyle(FILLEDMESH);
    //}
    //else if (action == wireframe)
    //{
    //  widget_->plot3d->setPlotStyle(WIREFRAME);
    //}
    //else if (action == hiddenline)
    //{
    //  widget_->plot3d->setPlotStyle(HIDDENLINE);
    //}
    //else if (action == pointstyle)
    //{
    //  widget_->plot3d->setPlotStyle(Traits3D::POINTS);
    //}
    //else
    //{
    //  widget_->plot3d->setPlotStyle(NOPLOT);
    //}
    //widget_->updateData();
}

void
MeshMainWindow::pickFloorStyle(QAction *action)
{
    //if (!action || !widget_)
    //  return;
    //if (action == floordata)
    //{
    //  widget_->plot3d->setFloorStyle(FLOORDATA);
    //}
    //else if (action == flooriso)
    //{
    //  widget_->plot3d->setFloorStyle(FLOORISO);
    //}
    //else
    //{
    //  widget_->plot3d->setFloorStyle(NOFLOOR);
    //}
    //
    //widget_->updateData();
}

void MeshMainWindow::setLeftGrid(bool b)
{
    setGrid(LEFT, b);
}
void MeshMainWindow::setRightGrid(bool b)
{
    setGrid(RIGHT, b);
}
void MeshMainWindow::setCeilGrid(bool b)
{
    setGrid(CEIL, b);
}
void MeshMainWindow::setFloorGrid(bool b)
{
    setGrid(FLOOR, b);
}
void MeshMainWindow::setFrontGrid(bool b)
{
    setGrid(FRONT, b);
}
void MeshMainWindow::setBackGrid(bool b)
{
    setGrid(BACK, b);
}

void MeshMainWindow::setGrid(SIDE s, bool b)
{
    if (!widget_)
        return;

    int sum = widget_->plot3d->coordinates()->grids();

    if (b)
        sum |= s;
    else
        sum &= ~s;

    widget_->plot3d->coordinates()->setGridLines(sum != NOSIDEGRID, sum != NOSIDEGRID, sum);
    widget_->update();
}

void MeshMainWindow::resetColors()
{
    if (!widget_)
        return;

    const Color axc = Color(0, 0, 0, 1);
    const Color bgc = Color(1.0, 1.0, 1.0, 1.0);
    const Color msc = Color(0, 0, 0, 1);
    const Color nuc = Color(0, 0, 0, 1);
    const Color lbc = Color(0, 0, 0, 1);
    const Color tc = Color(0, 0, 0, 1);
    widget_->plot3d->coordinates()->setAxesColor(axc);
    widget_->plot3d->setBackgroundColor(bgc);
    widget_->plot3d->setMeshColor(msc);
    widget_->updateData();
    widget_->plot3d->coordinates()->setNumberColor(nuc);
    widget_->plot3d->coordinates()->setLabelColor(lbc);
    widget_->plot3d->setTitleColor(tc);
    widget_->plot3d->setDataColor(ColorTable::stdColor(100));
    widget_->updateData();
    //  widget_->plot3d->updateNormals();
    widget_->update();
}


void MeshMainWindow::pickAxesColor()
{
    QColor c = QColorDialog::getColor(Qt::white, this);

    if (!c.isValid())
        return;

    Color rgb = Qt2GL(c);
    widget_->plot3d->coordinates()->setAxesColor(rgb);
    widget_->update();
}

void MeshMainWindow::pickBgColor()
{
    QColor c = QColorDialog::getColor(Qt::white, this);

    if (!c.isValid())
        return;

    Color rgb = Qt2GL(c);
    widget_->plot3d->setBackgroundColor(rgb);
    widget_->update();
}

void MeshMainWindow::pickMeshColor()
{
    QColor c = QColorDialog::getColor(Qt::white, this);

    if (!c.isValid())
        return;

    Color rgb = Qt2GL(c);
    widget_->plot3d->setMeshColor(rgb);
    widget_->updateData();
}

void MeshMainWindow::pickNumberColor()
{
    QColor c = QColorDialog::getColor(Qt::white, this);

    if (!c.isValid())
        return;

    Color rgb = Qt2GL(c);
    widget_->plot3d->coordinates()->setNumberColor(rgb);
    widget_->update();
}

void MeshMainWindow::pickLabelColor()
{
    QColor c = QColorDialog::getColor(Qt::white, this);

    if (!c.isValid())
        return;

    Color rgb = Qt2GL(c);
    widget_->plot3d->coordinates()->setLabelColor(rgb);
    widget_->update();
}
void MeshMainWindow::pickTitleColor()
{
    QColor c = QColorDialog::getColor(Qt::white, this);

    if (!c.isValid())
        return;

    Color rgb = Qt2GL(c);
    widget_->plot3d->setTitleColor(rgb);
    widget_->update();
}

void MeshMainWindow::pickLighting()
{
    //  lightingdlg_->show();
}

void MeshMainWindow::pickDataColor()
{
    //resetColors();
    //QString s =  QFileDialog::getOpenFileName( this, "", "./../../../src/examples/qt/resources/colormaps", "Colormap files (*.map *.MAP)");
    QString s =  QFileDialog::getOpenFileName(this, "", "assets:/colormaps", "Colormap files (*.map *.MAP)");
    adaptDataColors(s);
}

void MeshMainWindow::adaptDataColors(const QString &fileName)
{
    ColorVector cv;

    if (!openColorMap(cv, fileName))
        return;

    widget_->plot3d->setDataColor(cv);
    widget_->updateData();
    //  widget_->plot3d->updateNormals();
    //  widget_->plot3d->showColorLegend(legend_);
    widget_->update();
}

void MeshMainWindow::pickNumberFont()
{
    //bool ok;
    //QFont font = QFontDialog::getFont(&ok, this );
    //if ( !ok )
    //{
    //  return;
    //}
    //widget_->plot3d->coordinates()->setNumberFont(font);
    //widget_->update();
}
void MeshMainWindow::pickLabelFont()
{
    //bool ok;
    //QFont font = QFontDialog::getFont(&ok, this );
    //if ( !ok )
    //{
    //  return;
    //}
    //widget_->plot3d->coordinates()->setLabelFont(font);
    //widget_->update();
}
void MeshMainWindow::pickTitleFont()
{
    //bool ok;
    //QFont font = QFontDialog::getFont(&ok, this );
    //if ( !ok )
    //{
    //  return;
    //}
    //widget_->plot3d->setTitleFont(font);
}

void MeshMainWindow::resetFonts()
{
    //widget_->plot3d->coordinates()->setNumberFont(QFont("Courier", 12));
    //widget_->plot3d->coordinates()->setLabelFont(QFont("Courier", 14, QFont::Bold));
    //widget_->plot3d->setTitleFont(QFont("Arial", 14, QFont::Normal));
    //widget_->update();
}

void MeshMainWindow::setStandardView()
{
    widget_->setRotation(deg2rad(30), 0, deg2rad(15));
    widget_->setViewportShift(0.05f, 0);
    widget_->setScale(1, 1, 1);
    widget_->setZoom(0.95f);
}

/*!
  Turns animation on or off
*/
void MeshMainWindow::toggleAnimation(bool val)
{
    if (val)
    {
        timer_->start(redraw_wait_);   // Wait this many msecs before redraw
    }
    else
        timer_->stop();
}

void MeshMainWindow::rotate()
{
    if (!widget_)
        return;

    float step = 0.5f / PI;
    float PI2 = PI * 2;
    widget_->plot3d->setRotation(
        std::fmod(widget_->plot3d->xRotation() + step, PI2),
        std::fmod(widget_->plot3d->yRotation() + step, PI2),
        std::fmod(widget_->plot3d->zRotation() + step, PI2)
    );
    widget_->update();
}

void
MeshMainWindow::toggleProjectionMode(bool val)
{
    widget_->plot3d->setOrtho(val);
}

void
MeshMainWindow::toggleColorLegend(bool val)
{
    //legend_ = val;
    //widget_->plot3d->showColorLegend(val);
}

void
MeshMainWindow::toggleAutoScale(bool val)
{
    widget_->plot3d->coordinates()->setAutoScale(val);
    widget_->update();
}

void
MeshMainWindow::toggleShader(bool val)
{
    //if (val)
    //  widget_->plot3d->setShading(GOURAUD);
    //else
    //  widget_->plot3d->setShading(FLAT);
}

void
MeshMainWindow::setPolygonOffset(int val)
{
    //widget_->plot3d->setPolygonOffset(val / 10.0);
    //widget_->updateData();
}

void
MeshMainWindow::showRotate(double x, double y, double z)
{
    rotate_label_->setText(" Angles ("
                           + QString::number(rad2deg(x), 'g', 3) + " ,"
                           + QString::number(rad2deg(y), 'g', 3) + " ,"
                           + QString::number(rad2deg(z), 'g', 3) + ")");
}
void
MeshMainWindow::showShift(double x, double y)
{
    shift_label_->setText(" Shifts (" + QString::number(x, 'g', 3) + " ,"
                          + QString::number(y, 'g', 3) + " )"
                         );
}
void
MeshMainWindow::showScale(double x, double y, double z)
{
    scale_label_->setText(" Scales (" + QString::number(x, 'g', 3) + " ,"
                          + QString::number(y, 'g', 3) + " ,"
                          + QString::number(z, 'g', 3) + ")");
}
void
MeshMainWindow::showZoom(double z)
{
    zoom_label_->setText(" Zoom "  + QString::number(z, 'g', 3));
}

void
MeshMainWindow::showNormals(bool val)
{
    //widget_->plot3d->showNormals(val);
    //widget_->plot3d->updateNormals();
    //widget_->update();
}

void
MeshMainWindow::setNormalLength(int val)
{
    //widget_->plot3d->setNormalLength(val / 400.);
    //widget_->plot3d->updateNormals();
    //widget_->update();
}

void
MeshMainWindow::setNormalQuality(int val)
{
    //widget_->plot3d->setNormalQuality(val);
    //widget_->plot3d->updateNormals();
    //widget_->update();
}

bool
MeshMainWindow::openColorMap(ColorVector &cv, QString fname)
{
    if (fname.isEmpty())
        return false;

    ifstream file(fname.toLocal8Bit().constData());

    if (!file)
        return false;

    Color rgb;
    cv.clear();

    while (file)
    {
        file >> rgb.r >> rgb.g >> rgb.b;
        file.ignore(1000, '\n');

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
    //widget_->plot3d->legend()->setMajors(majors);
    //widget_->plot3d->legend()->setMinors(minors);
    //double start, stop;
    //widget_->plot3d->coordinates()->axes[Z1].limits(start,stop);
    //widget_->plot3d->legend()->setLimits(start, stop);
}

void MeshMainWindow::enableLighting(bool val)
{
    widget_->plot3d->enableLighting(val);
    widget_->plot3d->illuminate(0);
    widget_->update();
}
