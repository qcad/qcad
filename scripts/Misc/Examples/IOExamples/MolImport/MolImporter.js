/**
 * Copyright (c) 2013 by Matthias Melcher. All rights reserved.
 * 
 * This file is an addition to the QCAD project.
 *
 * MOL Import is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MOL Import is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("scripts/ShapeAlgorithms.js");

/**
 * \class MolImporter
 * \brief Very basic MOL import implementation. 
 */
function MolImporter(document) {
    RFileImporterAdapter.call(this, document);
    this.setDocument(document);
}

MolImporter.prototype = new RFileImporterAdapter();

MolImporter.includeBasePath = includeBasePath;


// LEETRO float: [eeeeeeee|smmmmmmm|mmmmmmm0|00000000]
MolImporter.prototype.readFloat = function(file) {
  var v = 0;
  var vExp = 0;
  var vMnt = 0;
  var vSgn = 1;
  var b = file.read(4);
 
  vExp = b.at(3);

  var b1 = b.at(1); if (b1<0) b1 = 256+b1;
  var b2 = b.at(2); if (b2<0) b2 = 256+b2;
  if (b2>127) b2 = b2 - 128;
  vMnt = b1/2 + 128*b2 + 0x4000;

  if (b.at(2)<0) vSgn = -1;

  v = (vMnt/16384.0)*Math.pow(2,vExp); 

  //qDebug("ReadFloat: ", v, vExp, vMnt, vSgn);
  return v;
}


MolImporter.prototype.readUWord = function(file) {
  var v = 0;
  var b = file.read(4);
  for (var i=3; i>=0; --i) {
    var d = b.at(i); 
    if (d<0) d = 256+d;
    v = v * 256 + d;
  }
  return v;
}


MolImporter.prototype.readWord = function(file) {
  var v = this.readUWord(file);
  if (v>=0x80000000) {
    v = v - 0x80000000;
    v = -0x80000000 + v;
  }
  return v;
}


MolImporter.prototype.importFile = function(fileName) {
    if (isNull(this.getDocument())) {
        this.setDocument(EAction.getDocument());
    }

    var fi = new QFileInfo(fileName);

    var file = new QFile(fi.absoluteFilePath());
    file.open(QIODevice.ReadOnly);

    var fileSize = this.readUWord(file); // 0x00
    var nMotionBlocks = this.readUWord(file);	// 0x04
    this.readWord(file);	// 0x08
    this.readWord(file);	// 0x0c
    this.readWord(file);	// 0x10
    this.readWord(file);	// 0x14
    var xMax = this.readWord(file);	// 0x18
    var yMax = this.readWord(file);	// 0x1c
    var xMin = this.readWord(file);	// 0x20
    var yMin = this.readWord(file);	// 0x24
    file.seek(0x00000070);
    var cfgData = this.readWord(file) * 512;	// 0x70
    this.readWord(file);	// 0x74
    this.readWord(file);	// 0x78
    var cutData = this.readWord(file) * 512;	// 0x7c

    var done = 0;
    var px = 0;
    var py = 0;
    var firstMove = 0;
    var xyScale = 208.33;

    file.seek(cfgData);
    while (!file.atEnd() && !done) {
      var cmd = this.readUWord(file);
      switch (cmd) {
        case 0x03026000: // move to first cut
        case 0x03026040:
          // in LAMPS.MOL, this code occurs twice!
          if (firstMove) break;
          firstMove = 1;
          this.readUWord(file);
          px = this.readWord(file);
          py = this.readWord(file);
          break;
        case 0x03000e46: // set stepper scale
          xyScale = this.readFloat(file);
          this.readFloat(file);
          this.readFloat(file); // z scale
          break;
        case 0x00200648: // end of soubroutine
        case 0x00000000:
          done = 1;
          break;
        default:
          var nWords = cmd>>24;
          if (nWords==0x80 || nWords==-128) nWords = this.readUWord(file);
          //qDebug("Skipping ", nWords, " words at ", file.pos());
          file.seek(file.pos()+4*nWords);
          break;
      }
    }

    xMax /= xyScale; yMax /= xyScale; xMin /= xyScale; yMin /= xyScale;
    
    var line = new RLine(new RVector(xMin, yMin), new RVector(xMin, yMax));
    var entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
    line = new RLine(new RVector(xMin, yMax), new RVector(xMax, yMax));
    entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
    line = new RLine(new RVector(xMax, yMax), new RVector(xMax, yMin));
    entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
    line = new RLine(new RVector(xMax, yMin), new RVector(xMin, yMin));
    entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);

    var progressDialog = new QProgressDialog(
        qsTr("Importing Leetro MOL file..."),
        qsTr("Abort"), 0, nMotionBlocks);
    progressDialog.windowModality = Qt.WindowModal;
    progressDialog.setCancelButton(null);

    var laserIsOn = 0;
    var spdMin = 100;
    var spdMax = 100;
    done = 0;
    file.seek(cutData);
    while (!file.atEnd() && !done) {
      var cmd = this.readUWord(file);
      switch (cmd) {
        case 0x80000946: // begin motion block
          this.readUWord(file);
          progressDialog.value++;
          //if (progressDialog.wasCanceled()) done = 1;
          break;
        case 0x01000606: // switch laser
          laserIsOn = this.readUWord(file);
          break;
        case 0x03000301: // set speeds
          spdMin = this.readFloat(file)/xyScale; // float: min
          spdMax = this.readFloat(file)/xyScale; // float: max
          this.readFloat(file); // float: accel
          break;
        case 0x03026000: // move relative
          var axis = this.readUWord(file);
          var dx = this.readWord(file);
          var dy = this.readWord(file);
          var line = new RLine(new RVector(px/xyScale, py/xyScale), new RVector((px+dx)/xyScale, (py+dy)/xyScale));
          var entity = new RLineEntity(this.getDocument(), new RLineData(line));
          if (laserIsOn) {
            var avg = (spdMin+spdMax)/2.0; 
            if (avg>100) avg = 100;
            var r = 255;
            var g = Math.min(avg, 50) * 5.11;
            var b = Math.max(0, avg-50) * 5.11;
            entity.setColor(new RColor(r, g, b));
          } else {
            entity.setColor(new RColor(255,255,255, 128));
          }
          this.importObject(entity);
          px = px + dx; py = py + dy;
          break;
        case 0x01400048: // end of soubroutine
        case 0x00000000:
          done = 1;
          break;
        default:
          var nWords = cmd>>24;
          if (nWords==0x80 || nWords==-128) nWords = this.readUWord(file);
          //qDebug("Skipping ", nWords, " words at ", file.pos());
          file.seek(file.pos()+4*nWords);
          break;
      }
    }

    progressDialog.reset();

    file.close();

    this.endImport();

    return true;
};

