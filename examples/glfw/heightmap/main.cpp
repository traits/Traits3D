#include "Window/Window.h"

#include "glb/vao.h"
#include "heightmap.h"


using namespace traits3d;

int main()
{
    HeightMap hm;
    // set OpenGL context
    Example::Window w("GLFW OpenGL3 Heightmap Demo");

    if (!hm.initializeGL())
        return false;

    if (!hm.loadData())
        return -1;

    hm.setRotation(deg2rad(30), 0, deg2rad(45));
    hm.setBackgroundColor(Color(1, 1, 1, 1));
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

