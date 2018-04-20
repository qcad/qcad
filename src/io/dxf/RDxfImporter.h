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

#include "dxflib/src/dl_creationadapter.h"

#include "RDimensionEntity.h"
#include "RDocument.h"
#include "RDxfServices.h"
#include "RFileImporter.h"
#include "RHatchData.h"
#include "RLeaderData.h"
#include "RPolyline.h"
#include "RSpline.h"

class RDxfImporter;
class RImageEntity;
class RMessageHandler;
class RProgressHandler;
class RVector;


/**
 * Represents a text style.
 * \ingroup dxf
 */
class QCADDXF_EXPORT RDxfTextStyle {
public:
    RDxfTextStyle() : bold(false), italic(false) {}

    QString font;
    bool bold;
    bool italic;
};


/**
 * \brief Importer for the DXF format, based on the dxflib library.
 *
 * \ingroup dxf
 */
class QCADDXF_EXPORT RDxfImporter : public RFileImporter, public DL_CreationAdapter {
public:
    RDxfImporter(RDocument& document,
        RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL);
    virtual ~RDxfImporter();

    virtual bool importFile(const QString& fileName, const QString& nameFilter);

    virtual void processCodeValuePair(unsigned int groupCode, const std::string& groupValue);

private:
    // Methods from DL_CreationInterface:
    virtual void addLayer(const DL_LayerData& data);
    virtual void addLinetype(const DL_LinetypeData& data);
    virtual void addLinetypeDash(double length);
    virtual void addBlock(const DL_BlockData& data);
    virtual void endBlock();
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);
    virtual void addXLine(const DL_XLineData& data);
    virtual void addRay(const DL_RayData& data);
    virtual void addArc(const DL_ArcData& data);
    virtual void addEllipse(const DL_EllipseData& data);
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void endEntity();
    virtual void endSection();
    virtual void addSpline(const DL_SplineData& data);
    virtual void addControlPoint(const DL_ControlPointData& data);
    virtual void addFitPoint(const DL_FitPointData& data);
    virtual void addKnot(const DL_KnotData& data);
    virtual void addInsert(const DL_InsertData& data);
    virtual void addSolid(const DL_SolidData& data);
    virtual void addTrace(const DL_TraceData& data);
    virtual void addTextStyle(const DL_StyleData& data);
    virtual void addMTextChunk(const std::string& text);
    virtual void addMText(const DL_MTextData& data);
    RTextBasedData getTextBasedData(const DL_TextData& data);
    virtual void addText(const DL_TextData& data);
    virtual void addArcAlignedText(const DL_ArcAlignedTextData& data);
    virtual void addAttribute(const DL_AttributeData& data);
    virtual RDimensionData convDimensionData(const DL_DimensionData& data);
    virtual void addDimAlign(const DL_DimensionData& data, const DL_DimAlignedData& edata);
    virtual void addDimLinear(const DL_DimensionData& data, const DL_DimLinearData& edata);
    virtual void addDimRadial(const DL_DimensionData& data, const DL_DimRadialData& edata);
    virtual void addDimDiametric(const DL_DimensionData& data, const DL_DimDiametricData& edata);
    virtual void addDimAngular(const DL_DimensionData& data, const DL_DimAngular2LData& edata);
    virtual void addDimAngular3P(const DL_DimensionData& data, const DL_DimAngular3PData& edata);
    virtual void addDimOrdinate(const DL_DimensionData& data, const DL_DimOrdinateData& edata);
    virtual void addLeader(const DL_LeaderData &data);
    virtual void addLeaderVertex(const DL_LeaderVertexData &data);
    virtual void addHatch(const DL_HatchData& data);
    virtual void addHatchLoop(const DL_HatchLoopData& data);
    virtual void addHatchEdge(const DL_HatchEdgeData& data);
    virtual void addImage(const DL_ImageData &data);
    virtual void linkImage(const DL_ImageDefData &data);

    virtual void addXRecord(const std::string& handle);
    virtual void addXRecordString(int code, const std::string& value);
    virtual void addXRecordReal(int code, double value);
    virtual void addXRecordInt(int code, int value);
    virtual void addXRecordBool(int code, bool value);

    virtual void addXDataApp(const std::string& appId);
    virtual void addXDataString(int code, const std::string& value);
    virtual void addXDataReal(int code, double value);
    virtual void addXDataInt(int code, int value);

    virtual void addDictionary(const DL_DictionaryData& data);
    virtual void addDictionaryEntry(const DL_DictionaryEntryData& data);

    virtual void setVariableVector(const std::string& key, double v1, double v2, double v3, int code);
    virtual void setVariableString(const std::string& key, const std::string& value, int code);
    virtual void setVariableInt(const std::string& key, int value, int code);
    virtual void setVariableDouble(const std::string& key, double value, int code);

    static QString decode(const QString& str);

private:
    static QString getEncoding(const QString& str);

    void importEntity(QSharedPointer<REntity> entity);

    QString getXDataString(const QString& appId, int code, int pos=0);
    int getXDataInt(const QString& appId, int code, int pos=0);

private:
    QString fileName;
    RDxfServices dxfServices;
    // list of locked layers. layers are locked after importing all entities:
    QStringList lockedLayers;

    RPolyline polyline;
    bool polylinePlineGen;
    RSpline spline;
    RLeaderData leader;
    bool leaderArrowHead;
    RHatchData hatch;
    QByteArray mtext;
    QMap<QString, RDxfTextStyle> textStyles;
    QMultiMap<int, RObject::Id> images;
    // pattern for linetype
    QList<double> pattern;

    // Current app id for XData:
    QString xDataAppId;
    // AppID -> list of code / value pairs
    QMap<QString, QList<QPair<int, QVariant> > > xData;
    QString qcadDictHandle;
    bool inDict;
    // Dictionary handles -> names
    QMap<QString, QString> qcadDict;
    QString variableKey;
};

Q_DECLARE_METATYPE(RDxfImporter*)
Q_DECLARE_METATYPE(DL_CreationAdapter*)

#endif
