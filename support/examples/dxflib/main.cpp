#include "dl_dxf.h"

int main() {
    DL_Dxf dxf;
    DL_WriterA* dw = dxf.out("hatch.dxf", DL_Codes::AC1015);

    // section header:
    dxf.writeHeader(*dw);
    dw->sectionEnd();

    // section tables:
    { 
        dw->sectionTables();

        // VPORT:
        dxf.writeVPort(*dw);

        // LTYPE:
        dw->tableLineTypes(1);
        dxf.writeLineType(*dw, DL_LineTypeData("CONTINUOUS", 0));
        dw->tableEnd();

        // LAYER:
        dw->tableLayers(1);
        dxf.writeLayer(
            *dw,
            DL_LayerData("0", 0),
            DL_Attributes("", 2, 0, 100, "CONTINUOUS")
        );
        dw->tableEnd();

        // STYLE:
        dw->tableStyle(1);
        DL_StyleData style("Standard", 0, 0.0, 1.0, 0.0, 0, 2.5, "txt", "");
        style.bold = false;
        style.italic = false;
        dxf.writeStyle(*dw, style);
        dw->tableEnd();

        // VIEW:
        dxf.writeView(*dw);

        // UCS:
        dxf.writeUcs(*dw);

        // APPID:
        dw->tableAppid(1);
        dxf.writeAppid(*dw, "ACAD");
        dw->tableEnd();

        // DIMSTYLE:
        dxf.writeDimStyle(*dw, 2.5, 0.625, 0.625, 0.625, 2.5);

        // BLOCK_RECORD:
        dxf.writeBlockRecord(*dw);
        dw->tableEnd();

        dw->sectionEnd();
    }

    // BLOCK:
    dw->sectionBlocks();
    dxf.writeBlock(*dw, DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
    dxf.writeEndBlock(*dw, "*Model_Space");
    dw->sectionEnd();

    // ENTITIES:
    dw->sectionEntities();

    DL_Attributes attributes("0", 2, 0, -1, "BYLAYER");

    // start hatch with one loop:
    DL_HatchData data(1, false, 1.0, 0.0, "ESCHER", 0.0, 0.0);
    dxf.writeHatch1(*dw, data, attributes);

    // start loop:
    DL_HatchLoopData lData(1);
    dxf.writeHatchLoop1(*dw, lData);

    // write edge:
    DL_HatchEdgeData eData(
        0.0,
        0.0,
        100.0,
        0.0,
        M_PI*2,
        true
    );
    dxf.writeHatchEdge(*dw, eData);

    // end loop:
    dxf.writeHatchLoop2(*dw, lData);

    // end hatch:
    dxf.writeHatch2(*dw, data, attributes);

    // end section ENTITIES:
    dw->sectionEnd();

    dw->dxfEOF();
    dw->close();
    delete dw;

    return 0;
}
