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

#ifndef RBLOCKLISTENER_H
#define RBLOCKLISTENER_H

#include "core_global.h"

#include <QMetaType>

class RDocumentInterface;

/**
 * \brief Abstract base class for classes that are interested 
 * in being notified whenever a block has been added or changed.
 * This can for example be a widget that lists all blocks.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RBlockListener {
public:
    virtual ~RBlockListener() {}

    /**
     * This method is called whenever at least one block in the given
     * document has changed.
     */
    virtual void updateBlocks(RDocumentInterface* documentInterface) = 0;

    /**
     * This method is called when a different block becomes the new current block.
     */
    virtual void setCurrentBlock(RDocumentInterface* documentInterface) = 0;

    /**
     * This method is called to signal that no document is currently active.
     */
    virtual void clearBlocks() = 0;
};

Q_DECLARE_METATYPE(RBlockListener*)

#endif
