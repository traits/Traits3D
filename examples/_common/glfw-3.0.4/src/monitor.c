//========================================================================
// GLFW 3.0 - www.glfw.org
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2010 Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#include "internal.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#if defined(_MSC_VER)
 #include <malloc.h>
 /** A macro that defines strdup. */
 #define strdup _strdup
#endif

/**
 Lexical comparison function for GLFW video modes, used by qsort.

 \param firstPtr  The first pointer.
 \param secondPtr The second pointer.

 \return  An int.
 */
static int compareVideoModes(const void* firstPtr, const void* secondPtr)
{
    int firstBPP, secondBPP, firstSize, secondSize;
    GLFWvidmode* first = (GLFWvidmode*) firstPtr;
    GLFWvidmode* second = (GLFWvidmode*) secondPtr;

    // First sort on color bits per pixel

    firstBPP = first->redBits +
               first->greenBits +
               first->blueBits;
    secondBPP = second->redBits +
                second->greenBits +
                second->blueBits;

    if (firstBPP != secondBPP)
        return firstBPP - secondBPP;

    // Then sort on screen area, in pixels

    firstSize = first->width * first->height;
    secondSize = second->width * second->height;

    if (firstSize != secondSize)
        return firstSize - secondSize;

    // Lastly sort on refresh rate

    return first->refreshRate - second->refreshRate;
}

/**
 Retrieves the available modes for the specified monitor.

 \param [in,out]  monitor If non-null, the monitor.

 \return  An int.
 */
static int refreshVideoModes(_GLFWmonitor* monitor)
{
    int modeCount;
    GLFWvidmode* modes;

    if (monitor->modes)
        return GL_TRUE;

    modes = _glfwPlatformGetVideoModes(monitor, &modeCount);
    if (!modes)
        return GL_FALSE;

    qsort(modes, modeCount, sizeof(GLFWvidmode), compareVideoModes);

    free(monitor->modes);
    monitor->modes = modes;
    monitor->modeCount = modeCount;

    return GL_TRUE;
}

/**
 //////////////////////////////////////////////////////////////////////////
 GLFW event API
 /////////////////////////////////////////////////////////////////////////////.
 */
void _glfwInputMonitorChange(void)
{
    int i, j, monitorCount = _glfw.monitorCount;
    _GLFWmonitor** monitors = _glfw.monitors;

    _glfw.monitors = _glfwPlatformGetMonitors(&_glfw.monitorCount);

    // Re-use still connected monitor objects

    for (i = 0;  i < _glfw.monitorCount;  i++)
    {
        for (j = 0;  j < monitorCount;  j++)
        {
            if (_glfwPlatformIsSameMonitor(_glfw.monitors[i], monitors[j]))
            {
                _glfwDestroyMonitor(_glfw.monitors[i]);
                _glfw.monitors[i] = monitors[j];
                break;
            }
        }
    }

    // Find and report disconnected monitors (not in the new list)

    for (i = 0;  i < monitorCount;  i++)
    {
        _GLFWwindow* window;

        for (j = 0;  j < _glfw.monitorCount;  j++)
        {
            if (monitors[i] == _glfw.monitors[j])
                break;
        }

        if (j < _glfw.monitorCount)
            continue;

        for (window = _glfw.windowListHead;  window;  window = window->next)
        {
            if (window->monitor == monitors[i])
                window->monitor = NULL;
        }

        if (_glfw.callbacks.monitor)
            _glfw.callbacks.monitor((GLFWmonitor*) monitors[i], GLFW_DISCONNECTED);
    }

    // Find and report newly connected monitors (not in the old list)
    // Re-used monitor objects are then removed from the old list to avoid
    // having them destroyed at the end of this function

    for (i = 0;  i < _glfw.monitorCount;  i++)
    {
        for (j = 0;  j < monitorCount;  j++)
        {
            if (_glfw.monitors[i] == monitors[j])
            {
                monitors[j] = NULL;
                break;
            }
        }

        if (j < monitorCount)
            continue;

        if (_glfw.callbacks.monitor)
            _glfw.callbacks.monitor((GLFWmonitor*) _glfw.monitors[i], GLFW_CONNECTED);
    }

    _glfwDestroyMonitors(monitors, monitorCount);
}

/**
 //////////////////////////////////////////////////////////////////////////
 GLFW internal API
 /////////////////////////////////////////////////////////////////////////////.

 \param name      The name.
 \param widthMM   The width millimetres.
 \param heightMM  The height millimetres.
 */
_GLFWmonitor* _glfwCreateMonitor(const char* name, int widthMM, int heightMM)
{
    _GLFWmonitor* monitor = calloc(1, sizeof(_GLFWmonitor));
    monitor->name = strdup(name);
    monitor->widthMM = widthMM;
    monitor->heightMM = heightMM;

    return monitor;
}

/**
 Glfw destroy monitor.

 \param [in,out]  monitor If non-null, the monitor.
 */
void _glfwDestroyMonitor(_GLFWmonitor* monitor)
{
    if (monitor == NULL)
        return;

    _glfwFreeGammaArrays(&monitor->originalRamp);
    _glfwFreeGammaArrays(&monitor->currentRamp);

    free(monitor->modes);
    free(monitor->name);
    free(monitor);
}

/**
 Glfw destroy monitors.

 \param [in,out]  monitors  If non-null, the monitors.
 \param count               Number of.
 */
void _glfwDestroyMonitors(_GLFWmonitor** monitors, int count)
{
    int i;

    for (i = 0;  i < count;  i++)
        _glfwDestroyMonitor(monitors[i]);

    free(monitors);
}

/**
 Glfw choose video mode.

 \param [in,out]  monitor If non-null, the monitor.
 \param desired           The desired.

 \return  null if it fails, else a GLFWvidmode*.
 */
const GLFWvidmode* _glfwChooseVideoMode(_GLFWmonitor* monitor,
                                        const GLFWvidmode* desired)
{
    int i;
    unsigned int sizeDiff, leastSizeDiff = UINT_MAX;
    unsigned int rateDiff, leastRateDiff = UINT_MAX;
    unsigned int colorDiff, leastColorDiff = UINT_MAX;
    const GLFWvidmode* current;
    const GLFWvidmode* closest = NULL;

    if (!refreshVideoModes(monitor))
        return NULL;

    for (i = 0;  i < monitor->modeCount;  i++)
    {
        current = monitor->modes + i;

        colorDiff = abs((current->redBits + current->greenBits + current->blueBits) -
                        (desired->redBits + desired->greenBits + desired->blueBits));

        sizeDiff = abs((current->width - desired->width) *
                       (current->width - desired->width) +
                       (current->height - desired->height) *
                       (current->height - desired->height));

        if (desired->refreshRate)
            rateDiff = abs(current->refreshRate - desired->refreshRate);
        else
            rateDiff = UINT_MAX - current->refreshRate;

        if ((colorDiff < leastColorDiff) ||
            (colorDiff == leastColorDiff && sizeDiff < leastSizeDiff) ||
            (colorDiff == leastColorDiff && sizeDiff == leastSizeDiff && rateDiff < leastRateDiff))
        {
            closest = current;
            leastSizeDiff = sizeDiff;
            leastRateDiff = rateDiff;
            leastColorDiff = colorDiff;
        }
    }

    return closest;
}

/**
 Glfw compare video modes.

 \param first   The first.
 \param second  The second.

 \return  An int.
 */
int _glfwCompareVideoModes(const GLFWvidmode* first, const GLFWvidmode* second)
{
    return compareVideoModes(first, second);
}

/**
 Glfw split bits per pixel.

 \param bpp             The bits per pixel.
 \param [in,out]  red   If non-null, the red.
 \param [in,out]  green If non-null, the green.
 \param [in,out]  blue  If non-null, the blue.
 */
void _glfwSplitBPP(int bpp, int* red, int* green, int* blue)
{
    int delta;

    // We assume that by 32 the user really meant 24
    if (bpp == 32)
        bpp = 24;

    // Convert "bits per pixel" to red, green & blue sizes

    *red = *green = *blue = bpp / 3;
    delta = bpp - (*red * 3);
    if (delta >= 1)
        *green = *green + 1;

    if (delta == 2)
        *red = *red + 1;
}

/**
 //////////////////////////////////////////////////////////////////////////
 GLFW public API
 /////////////////////////////////////////////////////////////////////////////.

 \param [in,out]  count If non-null, number of.

 \return  null if it fails, else a GLFWmonitor**.
 */
GLFWAPI GLFWmonitor** glfwGetMonitors(int* count)
{
    *count = 0;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    *count = _glfw.monitorCount;
    return (GLFWmonitor**) _glfw.monitors;
}

/**
 Glfw get primary monitor.

 \return  null if it fails, else a GLFWmonitor*.
 */
GLFWAPI GLFWmonitor* glfwGetPrimaryMonitor(void)
{
    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    return (GLFWmonitor*) _glfw.monitors[0];
}

/**
 Glfw get monitor position.

 \param [in,out]  handle  If non-null, the handle.
 \param [in,out]  xpos    If non-null, the xpos.
 \param [in,out]  ypos    If non-null, the ypos.
 */
GLFWAPI void glfwGetMonitorPos(GLFWmonitor* handle, int* xpos, int* ypos)
{
    _GLFWmonitor* monitor = (_GLFWmonitor*) handle;
    _GLFW_REQUIRE_INIT();
    _glfwPlatformGetMonitorPos(monitor, xpos, ypos);
}

/**
 Glfw get monitor physical size.

 \param [in,out]  handle  If non-null, the handle.
 \param [in,out]  width   If non-null, the width.
 \param [in,out]  height  If non-null, the height.
 */
GLFWAPI void glfwGetMonitorPhysicalSize(GLFWmonitor* handle, int* width, int* height)
{
    _GLFWmonitor* monitor = (_GLFWmonitor*) handle;

    _GLFW_REQUIRE_INIT();

    if (width)
        *width = monitor->widthMM;
    if (height)
        *height = monitor->heightMM;
}

/**
 Glfw get monitor name.

 \param [in,out]  handle  If non-null, the handle.

 \return  null if it fails, else a char*.
 */
GLFWAPI const char* glfwGetMonitorName(GLFWmonitor* handle)
{
    _GLFWmonitor* monitor = (_GLFWmonitor*) handle;
    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    return monitor->name;
}

/**
 Callback, called when the glfw set monitor.

 \param cbfun The cbfun.

 \return  A GLFWmonitorfun.
 */
GLFWAPI GLFWmonitorfun glfwSetMonitorCallback(GLFWmonitorfun cbfun)
{
    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP_POINTERS(_glfw.callbacks.monitor, cbfun);
    return cbfun;
}

/**
 Glfw get video modes.

 \param [in,out]  handle  If non-null, the handle.
 \param [in,out]  count   If non-null, number of.

 \return  null if it fails, else a GLFWvidmode*.
 */
GLFWAPI const GLFWvidmode* glfwGetVideoModes(GLFWmonitor* handle, int* count)
{
    _GLFWmonitor* monitor = (_GLFWmonitor*) handle;

    *count = 0;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (!refreshVideoModes(monitor))
        return NULL;

    *count = monitor->modeCount;
    return monitor->modes;
}

/**
 Glfw get video mode.

 \param [in,out]  handle  If non-null, the handle.

 \return  null if it fails, else a GLFWvidmode*.
 */
GLFWAPI const GLFWvidmode* glfwGetVideoMode(GLFWmonitor* handle)
{
    _GLFWmonitor* monitor = (_GLFWmonitor*) handle;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    _glfwPlatformGetVideoMode(monitor, &monitor->currentMode);
    return &monitor->currentMode;
}

