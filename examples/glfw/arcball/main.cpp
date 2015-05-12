#include <iostream>

#include "arcballexample.h"											

#pragma comment( lib, "opengl32.lib" )								// Search For OpenGL32.lib While Linking

int main()
{
  ExampleArcBall ea;
  ea.initialize();

  //if (!hm.loadData())
  //  return -1;

  //hm.setRotation(30, 0, 45);
  //hm.setBackgroundColor(Traits3D::Color(1, 1, 1, 1));

  /* main loop */
  double last_update_time = glfwGetTime();

  while (!ea.window()->onClose())
  {

    /* Check the frame rate and update the heightmap if needed */
    double dt = glfwGetTime();
    //if ((dt - last_update_time) > 0.1)
    {
      ea.update();
      ea.draw();
      ea.window()->update();
      last_update_time = dt;
    }
  }
  return 0;
}
