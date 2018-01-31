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

#ifndef RPAINTERPATHDEVICE_H
#define RPAINTERPATHDEVICE_H

#include "core_global.h"

#include <QPaintDevice>

#include "RPainterPathEngine.h"

/**
 * Paint device that produces painter paths as output.
 *
 * \scriptable
 * \ingroup core
 */
class QCADCORE_EXPORT RPainterPathDevice : public QPaintDevice {
public:
    RPainterPathDevice();
    virtual ~RPainterPathDevice();
    QList<RPainterPath> getPainterPaths();

protected:
    QPaintEngine* paintEngine() const;

    virtual int metric(PaintDeviceMetric metric) const;

private:
    RPainterPathEngine* engine;
};

Q_DECLARE_METATYPE(RPainterPathDevice*)

#endif
