#pragma once

#include "qtwidget.hh"
#include "traits3d/surfaceplot.h"

#include "ui_meshmainwindowbase.h"

class QLabel;
class QTimer;
class QAction;
class QFileDialog;
class LightingDlg;
class ColorMapPreview;

class MeshMainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT
public:
    MeshMainWindow(QWidget *parent = 0);
    ~MeshMainWindow();

public slots:
    void open();

    void createFunction(QString const &name);
    void createPSurface(QString const &name);

    void pickCoordSystem(QAction *);
    void pickPlotStyle(QAction *);
    void pickFloorStyle(QAction *);
    void pickAxesColor();
    void pickBgColor();
    void pickMeshColor();
    void pickNumberColor();
    void pickLabelColor();
    void pickTitleColor();
    void pickDataColor();
    void pickLighting();
    void resetColors();
    void pickNumberFont();
    void pickLabelFont();
    void pickTitleFont();
    void resetFonts();
    void setStandardView();
    void toggleAnimation(bool);
    void toggleProjectionMode(bool);
    void toggleColorLegend(bool);
    void toggleAutoScale(bool val);
    void toggleShader(bool val);
    void rotate();
    void setPolygonOffset(int);

    void showRotate(double x, double y, double z);
    void showShift(double x, double y);
    void showScale(double x, double y, double z);
    void showZoom(double z);
    void showNormals(bool val);
    void setNormalQuality(int);
    void setNormalLength(int);
    bool openColorMap(traits3d::ColorVector &cv, QString fname);
    void adaptDataColors(const QString &);
    void updateColorLegend(int majors, int minors);

    void setLeftGrid(bool b);
    void setRightGrid(bool b);
    void setCeilGrid(bool b);
    void setFloorGrid(bool b);
    void setFrontGrid(bool b);
    void setBackGrid(bool b);
    void setGrid(traits3d::SIDE, bool);

    void enableLighting(bool val);

private:
    traits3d::QtWidget<traits3d::SurfacePlot> *widget_;

    QLabel *filename_widget_, *dim_widget_,
           *rotate_label_, *shift_label_, *scale_label_, *zoom_label_;

    QTimer *timer_;
    int redraw_wait_;

    QAction *active_coordinate_system_;

    bool legend_;
    //Traits3D::StandardColor* col_;

    QFileDialog *datacolordlg_;
    LightingDlg *lightingdlg_;
    QActionGroup *grids_;
};


