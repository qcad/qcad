#ifndef QTSCRIPTSHELL_QSIMPLEXMLNODEMODEL_H
#define QTSCRIPTSHELL_QSIMPLEXMLNODEMODEL_H

#include <qsimplexmlnodemodel.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSimpleXmlNodeModel : public QSimpleXmlNodeModel
{
public:
    QtScriptShell_QSimpleXmlNodeModel(const QXmlNamePool&  namePool);
    ~QtScriptShell_QSimpleXmlNodeModel();

    QVector<QXmlNodeModelIndex >  attributes(const QXmlNodeModelIndex&  element) const;
    QUrl  baseUri(const QXmlNodeModelIndex&  node) const;
    QXmlNodeModelIndex::DocumentOrder  compareOrder(const QXmlNodeModelIndex&  ni1, const QXmlNodeModelIndex&  ni2) const;
    QUrl  documentUri(const QXmlNodeModelIndex&  ni) const;
    QXmlNodeModelIndex  elementById(const QXmlName&  id) const;
    QXmlNodeModelIndex::NodeKind  kind(const QXmlNodeModelIndex&  ni) const;
    QXmlName  name(const QXmlNodeModelIndex&  ni) const;
    QVector<QXmlName >  namespaceBindings(const QXmlNodeModelIndex&  arg__1) const;
    QXmlNodeModelIndex  nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis  axis, const QXmlNodeModelIndex&  origin) const;
    QVector<QXmlNodeModelIndex >  nodesByIdref(const QXmlName&  idref) const;
    QXmlNodeModelIndex  root(const QXmlNodeModelIndex&  n) const;
    QString  stringValue(const QXmlNodeModelIndex&  node) const;
    QVariant  typedValue(const QXmlNodeModelIndex&  n) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSIMPLEXMLNODEMODEL_H
