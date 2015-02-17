//todo fix gl header include sequence
#include "heightmap.h"

#include <QThread>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>

#include "fborenderer.h"

class LogoInFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    LogoInFboRenderer()
    {
        hm.initializeGL();
        hm.loadData();
        hm.setRotation(30, 0, 45);
        hm.setBackgroundColor(Protean3D::Color(0.7f,0.7f,0.7f,1));
    }

    void render() {
        hm.draw();
        QThread::msleep(50);
        update();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) {
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
