#pragma once

#include <memory>
#include "global.h"
#include "protean3d/glbase/glhelper.h"
#include <QOpenGLWidget>
#include "inputdevice.h"
#include "protean3d/types.h"
#include "protean3d/extglwidget.h"

class QMouseEvent;
class QWheelEvent;
class QKeyEvent;

namespace Protean3D
{  
//! An enhanced QOpenGLWidget
/*!
  The class covers mouse/keyboard handling, lighting and basic transformations, like
  scaling, shifting and rotating objects.
*/
class EXAMPLE_EXPORT QtWidgetBase : public QOpenGLWidget
{
  Q_OBJECT

public:
  explicit QtWidgetBase(std::shared_ptr<ExtGLWidget> plot, QWidget * parent = 0, Qt::WindowFlags f = 0);
  virtual ~QtWidgetBase();

  void initializeGL() override;

  //! Embraces plot().updateData with makeCurrent() and updateGL() 
  void updateData();

  // input devices

	void assignMouse(MouseState xrot, MouseState yrot, MouseState zrot,
									 MouseState xscale, MouseState yscale, MouseState zscale,
									 MouseState zoom, MouseState xshift, MouseState yshift);
	
	bool mouseEnabled() const; //!< Returns true, if the widget accept mouse input from the user
	void assignKeyboard(
     KeyboardState xrot_n, KeyboardState xrot_p
    ,KeyboardState yrot_n, KeyboardState yrot_p
    ,KeyboardState zrot_n, KeyboardState zrot_p
		,KeyboardState xscale_n, KeyboardState xscale_p 
    ,KeyboardState yscale_n, KeyboardState yscale_p
    ,KeyboardState zscale_n, KeyboardState zscale_p
		,KeyboardState zoom_n, KeyboardState zoom_p
    ,KeyboardState xshift_n, KeyboardState xshift_p
    ,KeyboardState yshift_n, KeyboardState yshift_p
    );
	
	bool keyboardEnabled() const; //!< Returns true, if the widget accept keyboard input from the user
  //! Sets speed for keyboard driven transformations
  void setKeySpeed(double rot, double scale, double shift); 
  //! Gets speed for keyboard driven transformations
  void keySpeed(double& rot, double& scale, double& shift) const;   

signals:
	//! Emitted, if the rotation is changed
  void rotationChanged( double xAngle, double yAngle, double zAngle ); 
	//! Emitted, if the shift is changed
	void shiftChanged( double xShift, double yShift, double zShift );
	//! Emitted, if the viewport shift is changed
	void vieportShiftChanged( double xShift, double yShift );
	//! Emitted, if the scaling is changed
  void scaleChanged( double xScale, double yScale, double zScale );
	//! Emitted, if the zoom is changed
	void zoomChanged(double);
	//! Emitted, if the projection mode is changed
  void projectionChanged(bool);

public slots:
	void setRotation( double xVal, double yVal, double zVal ); 																														
	void setShift( double xVal, double yVal, double zVal );    																														
	void setViewportShift( double xVal, double yVal );         																														
	void setScale( double xVal, double yVal, double zVal );    																														
	void setZoom( double );                                    																														
  void setOrtho(bool);                                       																														
  
	void enableMouse(bool val=true); //!< Enable mouse input   																														
	void disableMouse(bool val =true); //!< Disable mouse input																														
	void enableKeyboard(bool val=true); //!< Enable keyboard input   																														
	void disableKeyboard(bool val =true); //!< Disable keyboard input																														

  void enableLighting(bool val = true); //!< Turn Lighting on or off
  void disableLighting(bool val = true); //!< Turn Lighting on or off
  //! Rotate lightsource[idx]
  void setLightRotation( double xVal, double yVal, double zVal, unsigned int idx = 0 ); 																														
  //! Shift lightsource[idx]
	void setLightShift( double xVal, double yVal, double zVal, unsigned int idx = 0 );    																														


protected:
  std::shared_ptr<ExtGLWidget> plot_p;
  void paintGL() override;
  void resizeGL( int w, int h ) override;

private:	
  // mouse
  QPoint lastMouseMovePosition_;
	bool mpressed_;

	MouseState xrot_mstate_, 
			yrot_mstate_, 
			zrot_mstate_, 
			xscale_mstate_, 
			yscale_mstate_, 
			zscale_mstate_,
      zoom_mstate_,
			xshift_mstate_,
			yshift_mstate_;

	bool mouse_input_enabled_;

  void mousePressEvent( QMouseEvent *e );
  void mouseReleaseEvent( QMouseEvent *e );
  void mouseMoveEvent( QMouseEvent *e );
  void wheelEvent( QWheelEvent *e );		
  void keyPressEvent( QKeyEvent *e );

	void setRotationMouse(MouseState bstate, double accel, QPoint diff);
	void setScaleMouse(MouseState bstate, double accel, QPoint diff);
	void setShiftMouse(MouseState bstate, double accel, QPoint diff);

  // keyboard
	bool kpressed_;

	KeyboardState xrot_kstate_[2], 
			yrot_kstate_[2], 
			zrot_kstate_[2], 
			xscale_kstate_[2], 
			yscale_kstate_[2], 
			zscale_kstate_[2],
      zoom_kstate_[2],
			xshift_kstate_[2],
			yshift_kstate_[2];

	bool kbd_input_enabled_;
  double kbd_rot_speed_, kbd_scale_speed_, kbd_shift_speed_;

	void setRotationKeyboard(KeyboardState kseq, double speed);
	void setScaleKeyboard(KeyboardState kseq, double speed);
	void setShiftKeyboard(KeyboardState kseq, double speed);
};


} // ns


