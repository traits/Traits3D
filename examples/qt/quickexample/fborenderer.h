#pragma once

#include <QtQuick/QQuickFramebufferObject>

class HeightMap;

class FboInSGRenderer : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    Renderer *createRenderer() const;
};
