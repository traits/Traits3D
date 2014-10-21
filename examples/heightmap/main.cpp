#include "Window/Window.h"

#include "heightmap.h"




int main()
{
  Example::Window w;

  HeightMap hm;

  if (!hm.prepareDraw())
  {
    fprintf(stderr, "ERROR: during creation of the shader program\n");

    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  /* setup the scene ready for rendering */
  glViewport(0, 0, 1024, 768);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  /* main loop */
  double last_update_time = glfwGetTime();

  while (!glfwWindowShouldClose(w.window))
  {
    hm.draw();

    /* display and process events through callbacks */
    glfwSwapBuffers(w.window);
    glfwPollEvents();
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

