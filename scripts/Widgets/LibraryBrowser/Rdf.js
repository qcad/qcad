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

include("scripts/library.js");
include("db/Tag.js");
include("db/LocalePeer.js");

/**
 * SAX style XML handler.
 */
function RdfHandler(rdf) {
    QXmlDefaultHandler.call(this);
    this.context = "";
    this.language = "";
    this.rdf = rdf;
}

RdfHandler.prototype = new QXmlDefaultHandler();

/**
 * Handle element (tag).
 */
RdfHandler.prototype.startElement = function(namespaceURI, localName, qName, atts) {
    // ignore context of these container elements:
    if (localName==="RDF" || localName==="Bag" || localName==="li") {
        return true;
    }

    this.context = localName;
    this.language = atts.value("xml:lang");

    return true;
};

/**
 * Handle text data.
 */
RdfHandler.prototype.characters = function(ch) {
    if (ch.trim()==="") {
        return true;
    }

    // ignore for now:
    if (this.context==="created" ||
        this.context==="source") {
        return true;
    }

    var stem = undefined;
    // only stem single words:
    if (ch.indexOf(' ')===-1 && !isNull(this.language) && this.language.length!==0) {
        stem = RStemmer.stem(ch, this.language);
        if (stem===ch) {
            stem = undefined;
        }
    }

    this.rdf.tags.push(new Tag(this.context, this.language, ch, stem));

    return true;
};



/**
 * Creates an RDF object that represents the RDF file for the given resource.
 * The resource can be a file or a directory. For files the RDF file is
 * assumed to have the same base name with extension .rdf.
 * For directories, the RDF file is located in _META/meta.rdf.
 * If no RDF file exists for the resource, only some default meta information
 * is added (file name, modification time) [disabled for now].
 *
 * \param resource QFileInfo or path (string) of the resource.
 */
function Rdf(resource) {
    if (isString(resource)) {
        resource = new QFileInfo(resource);
    }

    // format: [category, locale, text]
    this.tags = [];

    // add some generic meta data that is available even without RDF:
    if (resource.completeBaseName().toLowerCase()!=="_meta") {
        this.tags.push(new Tag("file-name", Locale.Neutral, resource.completeBaseName()));
    }

    // look up RDF:
    this.fileInfo = Rdf.getRdfFileInfo(resource);
    this.fileName = this.fileInfo.absoluteFilePath();

    // no RDF found, done:
    if (!this.fileInfo.isFile()) {
        return;
    }

    if (!RSettings.isQt(5)) {
        //var file = new QFile(this.fileName);

        //var xmlReader = new QXmlSimpleReader();
        //var source = new QXmlInputSource(file);
        var handler = new RdfHandler(this);
        //xmlReader.setContentHandler(handler);
        //var ok = xmlReader.parse(source, false);
        parseXml(this.fileName, handler);

        //file.close();
    }
}

Rdf.xmlQuery = new QXmlQuery();

/**
 * \return QFileInfo File info for the RDF file that belongs to the 
 * given resource (e.g. dxf or svg file).
 */
Rdf.getRdfFileInfo = function(resource) {
    if (isString(resource)) {
        resource = new QFileInfo(resource);
    }

    // RDF for dir:
    if (resource.isDir()) {
        return new QFileInfo(resource.absoluteFilePath() + QDir.separator
            + "_META" + QDir.separator + "meta.rdf");
    }

    // RDF for file:
    return new QFileInfo(resource.absolutePath() + QDir.separator
            + resource.completeBaseName() + ".rdf");
};

/**
 * \return string Absolute file path with file name of RDF file.
 */
Rdf.prototype.getFileName = function() {
    return this.fileName;
};

/**
 * \return QFileInfo File info of this RDF file.
 */
Rdf.prototype.getFileInfo = function() {
    return this.fileInfo;
};


/**
 * \return string URL of this RDF file.
 */
Rdf.prototype.getUrl = function() {
    var file = this.getFileName();
    return QUrl.fromLocalFile(file).toString();
};

/**
 * \return Array with Tag items.
 */
Rdf.prototype.getTags = function() {
    return this.tags;
};
