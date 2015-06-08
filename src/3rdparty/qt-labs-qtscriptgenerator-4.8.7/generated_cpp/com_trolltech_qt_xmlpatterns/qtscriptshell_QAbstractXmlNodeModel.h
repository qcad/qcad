#ifndef QTSCRIPTSHELL_QABSTRACTXMLNODEMODEL_H
#define QTSCRIPTSHELL_QABSTRACTXMLNODEMODEL_H

#include <qabstractxmlnodemodel.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractXmlNodeModel : public QAbstractXmlNodeModel
{
public:
    QtScriptShell_QAbstractXmlNodeModel();
    ~QtScriptShell_QAbstractXmlNodeModel();

    QVector<QXmlNodeModelIndex >  attributes(const QXmlNodeModelIndex&  element) const;
    QUrl  baseUri(const QXmlNodeModelIndex&  ni) const;
    QXmlNodeModelIndex::DocumentOrder  compareOrder(const QXmlNodeModelIndex&  ni1, const QXmlNodeModelIndex&  ni2) const;
    QUrl  documentUri(const QXmlNodeModelIndex&  ni) const;
    QXmlNodeModelIndex  elementById(const QXmlName&  NCName) const;
    QXmlNodeModelIndex::NodeKind  kind(const QXmlNodeModelIndex&  ni) const;
    QXmlName  name(const QXmlNodeModelIndex&  ni) const;
    QVector<QXmlName >  namespaceBindings(const QXmlNodeModelIndex&  n) const;
    QXmlNodeModelIndex  nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis  axis, const QXmlNodeModelIndex&  origin) const;
    QVector<QXmlNodeModelIndex >  nodesByIdref(const QXmlName&  NCName) const;
    QXmlNodeModelIndex  root(const QXmlNodeModelIndex&  n) const;
    QString  stringValue(const QXmlNodeModelIndex&  n) const;
    QVariant  typedValue(const QXmlNodeModelIndex&  n) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTXMLNODEMODEL_H
