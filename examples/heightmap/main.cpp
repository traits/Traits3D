#include "Window/Window.h"

#include "heightmap.h"




int main()
{
  Example::Window w("GLFW OpenGL3 Heightmap Demo");

  HeightMap hm;

  if (!hm.prepareDraw())
    return -1;

  /* main loop */
  double last_update_time = glfwGetTime();

  while (!w.onClose())
  {
    hm.draw();
    w.update();

    /* Check the frame rate and update the heightmap if needed */
    double dt = glfwGetTime();
    if ((dt - last_update_time) > 0.001)
    {
      /* generate the next iteration of the heightmap */
      hm.prepareNextDraw();
      last_update_time = dt;
    }
  }
  return 0;
}

