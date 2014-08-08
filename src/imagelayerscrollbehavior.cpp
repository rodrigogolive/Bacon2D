#include <QtCore/qmath.h>

#include "imagelayerscrollbehavior.h"

#include "imagelayer.h"

ImageLayerScrollBehavior::ImageLayerScrollBehavior(QObject *parent)
    : ScrollBehaviorImpl(parent)
{
}

void ImageLayerScrollBehavior::update(const int &delta)
{
    Q_UNUSED(delta);

    ImageLayer *target = 0;
    if (!(target = dynamic_cast<ImageLayer*>(m_target)))
        return;


    int modifier = (target->layerType() == Layer::Mirrored) ? 2 : 1;

    qreal horizontalOffset = target->horizontalOffset() + m_horizontalStep;
    qreal verticalOffset = target->verticalOffset() + m_verticalStep;

    if (horizontalOffset <= -target->imageWidth() * modifier)
        horizontalOffset = 0;
    else if (horizontalOffset >= 0)
        horizontalOffset = -target->imageWidth() * modifier;

    if (verticalOffset <= -target->imageHeight() * modifier)
        verticalOffset = 0;
    else if (verticalOffset >= 0)
        verticalOffset = -target->imageHeight() * modifier;

    target->setHorizontalOffset(qCeil(horizontalOffset));
    target->setVerticalOffset(qCeil(verticalOffset));
}
