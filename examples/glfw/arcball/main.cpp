#include <iostream>
#include "arcballexample.h"											

int main()
{
  ExampleArcBall ea;

  if (!ea.initializeGL())
    return false;

  if (!ea.loadData())
    return -1;

  /* main loop */
  double last_update_time = glfwGetTime();

  while (!ea.window()->onClose())
  {

    /* Check the frame rate and update transformations if needed */
    double dt = glfwGetTime();
    if ((dt - last_update_time) > 0.01)
    {
      ea.update();
      ea.draw();
      ea.window()->update();
      last_update_time = dt;
    }
  }
  return 0;
}
