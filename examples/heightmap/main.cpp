#include <GLFW/glfw3.h> 

#include "heightmap.h"


/**********************************************************************
* GLFW callback functions
*********************************************************************/

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_ESCAPE:
    /* Exit program on Escape */
    glfwSetWindowShouldClose(window, GL_TRUE);
    break;
  }
}

int main()
{
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: Unable to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(1024, 768, "GLFW OpenGL3 Heightmap demo", NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  /* Register events callback */
  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  //glewExperimental = GL_TRUE;
  //if (GLEW_OK != glewInit())
  //{
  //  fprintf(stderr, "ERROR: unable to resolve OpenGL function pointers\n");
  //  glfwTerminate();
  //  exit(EXIT_FAILURE);
  //}

  HeightMap hm;

  if (!hm.prepareDraw())
  {
    fprintf(stderr, "ERROR: during creation of the shader program\n");

    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  /* setup the scene ready for rendering */
  glViewport(0, 0, 800, 600);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  /* main loop */
  double last_update_time = glfwGetTime();

  while (!glfwWindowShouldClose(window))
  {
    hm.draw();

    /* display and process events through callbacks */
    glfwSwapBuffers(window);
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

  glfwTerminate();
  return 0;
}

