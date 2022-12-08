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

#ifndef RDXFIMPORTER_H
#define RDXFIMPORTER_H

#include "dxf_global.h"

#include "RDimensionEntity.h"
#include "RDocument.h"
#include "RDxfServices.h"
#include "RFileImporter.h"
#include "RHatchData.h"
#include "RLeaderData.h"
#include "RPolyline.h"
#include "RSpline.h"
#include <libdxfrw/drw_interface.h>

class RDxfImporter;
class RImageEntity;
class RMessageHandler;
class RProgressHandler;
class RVector;

/**
 * \brief Importer for the DXF format, based on the dxflib library.
 *
 * \ingroup dxf
 */
class QCADDXF_EXPORT RDxfImporter : public RFileImporter, public DRW_Interface {
public:
    RDxfImporter(RDocument& document,
        RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL);
    virtual ~RDxfImporter();

    virtual bool importFile(const QString& fileName, const QString& nameFilter, const QVariantMap& params = RDEFAULT_QVARIANTMAP);

private:
#pragma region DRW_Interface
    /** Called when header is parsed.  */
    virtual void addHeader(const DRW_Header* data) override;

    /** Called for every line Type.  */
    virtual void addLType(const DRW_LType& data) override;
    /** Called for every layer. */
    virtual void addLayer(const DRW_Layer& data) override;
    /** Called for every dim style. */
    virtual void addDimStyle(const DRW_Dimstyle& data) override;
    /** Called for every VPORT table. */
    virtual void addVport(const DRW_Vport& data) override;
    /** Called for every text style. */
    virtual void addTextStyle(const DRW_Textstyle& data) override;
    /** Called for every AppId entry. */
    virtual void addAppId(const DRW_AppId& data) override;

    /**
     * Called for every block. Note: all entities added after this
     * command go into this block until endBlock() is called.
     *
     * @see endBlock()
     */
    virtual void addBlock(const DRW_Block& data) override;

    /**
     * In DWG called when the following entities corresponding to a
     * block different from the current. Note: all entities added after this
     * command go into this block until setBlock() is called already.
     *
     * int handle are the value of DRW_Block::handleBlock added with addBlock()
     */
    virtual void setBlock(const int handle) override;

    /** Called to end the current block */
    virtual void endBlock() override;

    /** Called for every point */
    virtual void addPoint(const DRW_Point& data) override;

    /** Called for every line */
    virtual void addLine(const DRW_Line& data) override;

    /** Called for every ray */
    virtual void addRay(const DRW_Ray& data) override;

    /** Called for every xline */
    virtual void addXline(const DRW_Xline& data) override;

    /** Called for every arc */
    virtual void addArc(const DRW_Arc& data) override;

    /** Called for every circle */
    virtual void addCircle(const DRW_Circle& data) override;

    /** Called for every ellipse */
    virtual void addEllipse(const DRW_Ellipse& data) override;

    /** Called for every lwpolyline */
    virtual void addLWPolyline(const DRW_LWPolyline& data) override;

    /** Called for every polyline start */
    virtual void addPolyline(const DRW_Polyline& data) override;

    /** Called for every spline */
    virtual void addSpline(const DRW_Spline* data) override;

    /** Called for every spline knot value */
    virtual void addKnot(const DRW_Entity& data) override;

    /** Called for every insert. */
    virtual void addInsert(const DRW_Insert& data) override;

    /** Called for every trace start */
    virtual void addTrace(const DRW_Trace& data) override;

    /** Called for every 3dface start */
    virtual void add3dFace(const DRW_3Dface& data) override;

    /** Called for every solid start */
    virtual void addSolid(const DRW_Solid& data) override;


    /** Called for every Multi Text entity. */
    virtual void addMText(const DRW_MText& data) override;

    /** Called for every Text entity. */
    virtual void addText(const DRW_Text& data) override;

    /**
     * Called for every aligned dimension entity.
     */
    virtual void addDimAlign(const DRW_DimAligned* data) override;
    /**
     * Called for every linear or rotated dimension entity.
     */
    virtual void addDimLinear(const DRW_DimLinear* data) override;

    /**
     * Called for every radial dimension entity.
     */
    virtual void addDimRadial(const DRW_DimRadial* data) override;

    /**
     * Called for every diametric dimension entity.
     */
    virtual void addDimDiametric(const DRW_DimDiametric* data) override;

    /**
     * Called for every angular dimension (2 lines version) entity.
     */
    virtual void addDimAngular(const DRW_DimAngular* data) override;

    /**
     * Called for every angular dimension (3 points version) entity.
     */
    virtual void addDimAngular3P(const DRW_DimAngular3p* data) override;

    /**
     * Called for every ordinate dimension entity.
     */
    virtual void addDimOrdinate(const DRW_DimOrdinate* data) override;

    /**
     * Called for every leader start.
     */
    virtual void addLeader(const DRW_Leader* data) override;

    /**
     * Called for every hatch entity.
     */
    virtual void addHatch(const DRW_Hatch* data) override;

    /**
     * Called for every viewport entity.
     */
    virtual void addViewport(const DRW_Viewport& data) override;

    /**
     * Called for every image entity.
     */
    virtual void addImage(const DRW_Image* data) override;

    /**
     * Called for every image definition.
     */
    virtual void linkImage(const DRW_ImageDef* data) override;

    /**
     * Called for every comment in the DXF file (code 999).
     */
    virtual void addComment(const char* comment) override;

    virtual void writeHeader(DRW_Header& data) {}
    virtual void writeBlocks() {}
    virtual void writeBlockRecords() {}
    virtual void writeEntities() {}
    virtual void writeLTypes() {}
    virtual void writeLayers() {}
    virtual void writeTextstyles() {}
    virtual void writeVports() {}
    virtual void writeDimstyles() {}
    virtual void writeAppId() {}
#pragma endregion
    void importEntity(QSharedPointer<REntity> entity, const DRW_Entity* data);
    static QString getEncoding(const QString& str);

    QStringList lockedLayers;
    QMap<QString, DRW_Textstyle> textStyles;
    QMap<QString, DRW_Dimstyle> dimStyles;
    QString decode(const QString& str);
    RDxfServices dxfServices;
};

Q_DECLARE_METATYPE(RDxfImporter*)

#endif
