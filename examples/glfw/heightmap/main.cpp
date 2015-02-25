#include "Window/Window.h"

#include "traits3d/glbase/vao.h"
#include "heightmap.h"




int main()
{
  HeightMap hm;

  // set OpenGL context
  Example::Window w("GLFW OpenGL3 Heightmap Demo");
  if (!hm.initializeGL())
    return false;

  if (!hm.loadData())
    return -1;

  hm.setRotation(30, 0, 45);

  /* main loop */
  double last_update_time = glfwGetTime();

  while (!w.onClose())
  {

    /* Check the frame rate and update the heightmap if needed */
    double dt = glfwGetTime();
    //if ((dt - last_update_time) > 0.1)
    {
      hm.draw();
      w.update();
      /* generate the next iteration of the heightmap */
      last_update_time = dt;
    }
  }
  return 0;
}

