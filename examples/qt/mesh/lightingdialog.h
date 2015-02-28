#pragma once

//#include <math.h>
//#include <qapplication.h>
//#include "protean3d/parametricsurface.h"
//#include "protean3d/qtwidget.hh"
//#include "protean3d/enrichment.h"
//#include "protean3d/color.h"
//
//#include "ui_lightingdialogbase.h"
//
//class Pointer : public Protean3D::UserEnrichment
//{
//public:
//  explicit Pointer(double rad);
//  
//  void configure(double rad);
//  void draw();
//  void setPos(double x, double y, double z) {pos_ = Protean3D::Triple(x,y,z);}
//
//private:
//  double radius_;
//  Protean3D::Triple pos_;
//};
//
//struct SColor : public Protean3D::Color
//{
//  Protean3D::RGBA operator()(double, double, double) const {return Protean3D::RGBA(0.8,0,0,0.5);}
//};
//
//typedef Protean3D::SurfacePlot SPlot; // moc/VC6 issue in Qt4
//
//class Plot : public Protean3D::QtWidget<Protean3D::SurfacePlot>
//{
//  Q_OBJECT
//    
//public:
//  Plot(QWidget* parent);
//  std::shared_ptr<Protean3D::Enrichment> stick;
//  void reset();
//};
//
//class LightingDlg : public QDialog, protected Ui::Dialog
//{
//	Q_OBJECT
//    
//public:
//  LightingDlg(QWidget *parent=0);
//  ~LightingDlg();
//
//  void assign(Protean3D::QtWidget<Protean3D::SurfacePlot>* pl);
//  
//public slots:
//	void setDistance(int);
//	void setEmission(int);
//	void setDiff(int);
//	void setSpec(int);
//	void setShin(int);
//  void reset();
//  void setRotation(double x, double y, double z);
//
//private:
//  Plot* plot_;
//  Protean3D::QtWidget<Protean3D::SurfacePlot>* data_plot_;
//};
//
//    

