#pragma once

//#include <math.h>
//#include <qapplication.h>
//#include "traits3d/parametricsurface.h"
//#include "traits3d/qtwidget.hh"
//#include "traits3d/enrichment.h"
//#include "traits3d/color.h"
//
//#include "ui_lightingdialogbase.h"
//
//class Pointer : public Traits3D::UserEnrichment
//{
//public:
//  explicit Pointer(double rad);
//  
//  void configure(double rad);
//  void draw();
//  void setPos(double x, double y, double z) {pos_ = Traits3D::Triple(x,y,z);}
//
//private:
//  double radius_;
//  Traits3D::Triple pos_;
//};
//
//struct SColor : public Traits3D::Color
//{
//  Traits3D::Color operator()(double, double, double) const {return Traits3D::Color(0.8,0,0,0.5);}
//};
//
//typedef Traits3D::SurfacePlot SPlot; // moc/VC6 issue in Qt4
//
//class Plot : public Traits3D::QtWidget<Traits3D::SurfacePlot>
//{
//  Q_OBJECT
//    
//public:
//  Plot(QWidget* parent);
//  std::shared_ptr<Traits3D::Enrichment> stick;
//  void reset();
//};
//
//class LightingDlg : public QDialog, protected Ui::Dialog
//{
//  Q_OBJECT
//    
//public:
//  LightingDlg(QWidget *parent=0);
//  ~LightingDlg();
//
//  void assign(Traits3D::QtWidget<Traits3D::SurfacePlot>* pl);
//  
//public slots:
//  void setDistance(int);
//  void setEmission(int);
//  void setDiff(int);
//  void setSpec(int);
//  void setShin(int);
//  void reset();
//  void setRotation(double x, double y, double z);
//
//private:
//  Plot* plot_;
//  Traits3D::QtWidget<Traits3D::SurfacePlot>* data_plot_;
//};
//
//    

