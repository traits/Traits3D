#include "Window/Window.h"

#include "protean3d/vao.h"
#include "heightmap.h"




int main()
{
  Example::Window w("GLFW OpenGL3 Heightmap Demo");

  //Protean3D::GL::VAO vao;

  //std::vector<GLfloat> testvec;
  //vao.appendVBO(testvec, Protean3D::GL::VBO::PrimitiveLayout(1, GL_FLOAT));

  // has to be placed after window creation (OpenGL initialization) at this moment
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

