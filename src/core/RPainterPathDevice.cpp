/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include "RPainterPathDevice.h"
#include "RMath.h"

RPainterPathDevice::RPainterPathDevice()
    : QPaintDevice(), size(100,100), dpi(96) {

    engine = new RPainterPathEngine();
}

RPainterPathDevice::~RPainterPathDevice() {
    delete engine;
}

QList<RPainterPath> RPainterPathDevice::getPainterPaths() {
    return engine->getPainterPaths();
}

QPaintEngine* RPainterPathDevice::paintEngine() const {
    return engine;
}

int RPainterPathDevice::metric(PaintDeviceMetric metric) const {
    switch (metric) {
    case QPaintDevice::PdmDepth:
        return 32;
    case QPaintDevice::PdmWidth:
        return size.width();
    case QPaintDevice::PdmHeight:
        return size.height();
    case QPaintDevice::PdmDpiX:
        return 72;
    case QPaintDevice::PdmDpiY:
        return 72;
    case QPaintDevice::PdmHeightMM:
        return RMath::mround(size.width() * 25.4 / dpi);
    case QPaintDevice::PdmWidthMM:
        return RMath::mround(size.height() * 25.4 / dpi);
    case QPaintDevice::PdmNumColors:
        return 0xffffffff;
    case QPaintDevice::PdmPhysicalDpiX:
        return 72;
    case QPaintDevice::PdmPhysicalDpiY:
        return 72;
#if QT_VERSION >= 0x050000
    case QPaintDevice::PdmDevicePixelRatio:
        return 1;
#endif
#if QT_VERSION >= 0x050600
    case QPaintDevice::PdmDevicePixelRatioScaled:
        return 1;
#endif
#if QT_VERSION >= 0x060800
    case QPaintDevice::PdmDevicePixelRatioF_EncodedA:
    case QPaintDevice::PdmDevicePixelRatioF_EncodedB:
        return QPaintDevice::encodeMetricF(metric, 1);
#endif
    default:
        qWarning("RPainterPathDevice::metric(), unhandled metric %d\n", metric);
        break;
    }
    return 0;
}
