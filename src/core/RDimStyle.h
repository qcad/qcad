/**
 * Copyright (c) 2011-2021 by Andrew Mustun. All rights reserved.
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

#ifndef RDIMSTYLE_H
#define RDIMSTYLE_H

#include "core_global.h"

#include "RDimStyleProxy.h"
#include "RObject.h"
#include "RPropertyTypeId.h"

class RDocument;
class REntityData;
class RExporter;

/**
 * Dimension style class.
 * This is responsible for rendering dimensions depending on style settings.
 *
 * \ingroup entity
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RDimStyle: public RObject {
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyProtected;

    static RPropertyTypeId PropertyDimscale;
    static RPropertyTypeId PropertyDimtxt;
    static RPropertyTypeId PropertyDimgap;
    static RPropertyTypeId PropertyDimtad;
    static RPropertyTypeId PropertyDimtih;

public:
    RDimStyle();

    RDimStyle(RDocument* document);
    virtual ~RDimStyle();

    static void init();

    void clear();

    virtual RS::EntityType getType() const {
        return RS::ObjectDimStyle;
    }

    virtual RDimStyle* clone() const {
        return new RDimStyle(*this);
    }

    QPair<QVariant, RPropertyAttributes> getProperty(RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest);
    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction);

    double getDimscale() const;
    void setDimscale(double v);
    double getDimtxt() const;
    void setDimtxt(double v);
    double getDimgap() const;
    void setDimgap(double v);
    double getDimasz() const;
    void setDimasz(double v);
    double getDimexe() const;
    void setDimexe(double v);
    double getDimexo() const;
    void setDimexo(double v);
    int getDimtad() const;
    void setDimtad(int v);
    int getDimtih() const;
    void setDimtih(int v);
    bool useArchTick() const;
    void setArchTick(bool on);

    void render(const REntityData& entityData, bool preview, bool forceSelected) {
        if (hasProxy()) {
            getDimStyleProxy()->render(*this, entityData, preview, forceSelected);
        }
        else {
            qWarning() << "no dimension style proxy registered";
        }
    }

    static bool hasProxy() {
        return dimStyleProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setDimStyleProxy(RDimStyleProxy* p) {
        if (dimStyleProxy!=NULL) {
            delete dimStyleProxy;
        }
        dimStyleProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RDimStyleProxy* getDimStyleProxy() {
        return dimStyleProxy;
    }

private:
    double dimscale;
    double dimtxt;
    double dimgap;
    double dimasz;
    double dimexe;
    double dimexo;
    int dimtad;
    int dimtih;
    bool archTick;

    // TODO:
    // Dimension text movement rules
    //int dimtmove;

    static RDimStyleProxy* dimStyleProxy;
};

Q_DECLARE_METATYPE(RDimStyle)
Q_DECLARE_METATYPE(RDimStyle*)
Q_DECLARE_METATYPE(const RDimStyle*)
Q_DECLARE_METATYPE(QSharedPointer<RDimStyle>)
Q_DECLARE_METATYPE(QSharedPointer<RDimStyle>*)

#endif
