//todo fix gl header include sequence
#include "heightmap.h"

#include <QThread>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>

#include "fborenderer.h"

using namespace traits3d;

class LogoInFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    LogoInFboRenderer()
    {
        hm.initializeGL();
        hm.loadData();
        hm.setRotation(deg2rad(30), 0, deg2rad(45));
        hm.setBackgroundColor(Color(0.0f, 197 / 255.0f, 205 / 255.0f, 1.0f)); // turquoise3
        hm.setTitle("Embedded FBO Plot");
    }

    void render()
    {
        hm.draw();
        QThread::msleep(50);
        update();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
    {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(1);
        return new QOpenGLFramebufferObject(size, format);
    }

    HeightMap hm;
};

QQuickFramebufferObject::Renderer *FboInSGRenderer::createRenderer() const
{
    return new LogoInFboRenderer();
}
