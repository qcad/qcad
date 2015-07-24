#include "qtscriptshell_QAccessibleTableInterface.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>
#include <qlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(QList<int>*)

QtScriptShell_QAccessibleTableInterface::QtScriptShell_QAccessibleTableInterface()
    : QAccessibleTableInterface() {}

QtScriptShell_QAccessibleTableInterface::~QtScriptShell_QAccessibleTableInterface() {}

QAccessibleInterface*  QtScriptShell_QAccessibleTableInterface::accessibleAt(int  row, int  column)
{
    QScriptValue _q_function = __qtscript_self.property("accessibleAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("accessibleAt") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::accessibleAt() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)));
    }
}

QAccessibleInterface*  QtScriptShell_QAccessibleTableInterface::caption()
{
    QScriptValue _q_function = __qtscript_self.property("caption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("caption") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::caption() is abstract!");
    } else {
        return qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QAccessibleTableInterface::cellAtIndex(int  index, int*  row, int*  column, int*  rowSpan, int*  columnSpan, bool*  isSelected)
{
    QScriptValue _q_function = __qtscript_self.property("cellAtIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("cellAtIndex") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::cellAtIndex() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, rowSpan)
            << qScriptValueFromValue(_q_engine, columnSpan)
            << qScriptValueFromValue(_q_engine, isSelected));
    }
}

int  QtScriptShell_QAccessibleTableInterface::childIndex(int  rowIndex, int  columnIndex)
{
    QScriptValue _q_function = __qtscript_self.property("childIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childIndex") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::childIndex() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rowIndex)
            << qScriptValueFromValue(_q_engine, columnIndex)));
    }
}

int  QtScriptShell_QAccessibleTableInterface::columnCount()
{
    QScriptValue _q_function = __qtscript_self.property("columnCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::columnCount() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

QString  QtScriptShell_QAccessibleTableInterface::columnDescription(int  column)
{
    QScriptValue _q_function = __qtscript_self.property("columnDescription");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnDescription") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::columnDescription() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)));
    }
}

QAccessibleInterface*  QtScriptShell_QAccessibleTableInterface::columnHeader()
{
    QScriptValue _q_function = __qtscript_self.property("columnHeader");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnHeader") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::columnHeader() is abstract!");
    } else {
        return qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleTableInterface::columnIndex(int  childIndex)
{
    QScriptValue _q_function = __qtscript_self.property("columnIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnIndex") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::columnIndex() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, childIndex)));
    }
}

int  QtScriptShell_QAccessibleTableInterface::columnSpan(int  row, int  column)
{
    QScriptValue _q_function = __qtscript_self.property("columnSpan");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnSpan") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::columnSpan() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)));
    }
}

bool  QtScriptShell_QAccessibleTableInterface::isColumnSelected(int  column)
{
    QScriptValue _q_function = __qtscript_self.property("isColumnSelected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isColumnSelected") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::isColumnSelected() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)));
    }
}

bool  QtScriptShell_QAccessibleTableInterface::isRowSelected(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("isRowSelected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isRowSelected") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::isRowSelected() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
    }
}

bool  QtScriptShell_QAccessibleTableInterface::isSelected(int  row, int  column)
{
    QScriptValue _q_function = __qtscript_self.property("isSelected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isSelected") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::isSelected() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)));
    }
}

int  QtScriptShell_QAccessibleTableInterface::rowCount()
{
    QScriptValue _q_function = __qtscript_self.property("rowCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::rowCount() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

QString  QtScriptShell_QAccessibleTableInterface::rowDescription(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("rowDescription");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowDescription") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::rowDescription() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
    }
}

QAccessibleInterface*  QtScriptShell_QAccessibleTableInterface::rowHeader()
{
    QScriptValue _q_function = __qtscript_self.property("rowHeader");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowHeader") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::rowHeader() is abstract!");
    } else {
        return qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleTableInterface::rowIndex(int  childIndex)
{
    QScriptValue _q_function = __qtscript_self.property("rowIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowIndex") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::rowIndex() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, childIndex)));
    }
}

int  QtScriptShell_QAccessibleTableInterface::rowSpan(int  row, int  column)
{
    QScriptValue _q_function = __qtscript_self.property("rowSpan");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowSpan") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::rowSpan() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)));
    }
}

void QtScriptShell_QAccessibleTableInterface::selectColumn(int  column)
{
    QScriptValue _q_function = __qtscript_self.property("selectColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectColumn") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::selectColumn() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column));
    }
}

void QtScriptShell_QAccessibleTableInterface::selectRow(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("selectRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectRow") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::selectRow() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row));
    }
}

int  QtScriptShell_QAccessibleTableInterface::selectedColumnCount()
{
    QScriptValue _q_function = __qtscript_self.property("selectedColumnCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedColumnCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::selectedColumnCount() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleTableInterface::selectedColumns(int  maxColumns, QList<int >*  columns)
{
    QScriptValue _q_function = __qtscript_self.property("selectedColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedColumns") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::selectedColumns() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, maxColumns)
            << qScriptValueFromValue(_q_engine, columns)));
    }
}

int  QtScriptShell_QAccessibleTableInterface::selectedRowCount()
{
    QScriptValue _q_function = __qtscript_self.property("selectedRowCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedRowCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::selectedRowCount() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleTableInterface::selectedRows(int  maxRows, QList<int >*  rows)
{
    QScriptValue _q_function = __qtscript_self.property("selectedRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedRows") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::selectedRows() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, maxRows)
            << qScriptValueFromValue(_q_engine, rows)));
    }
}

QAccessibleInterface*  QtScriptShell_QAccessibleTableInterface::summary()
{
    QScriptValue _q_function = __qtscript_self.property("summary");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("summary") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::summary() is abstract!");
    } else {
        return qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QAccessibleTableInterface::unselectColumn(int  column)
{
    QScriptValue _q_function = __qtscript_self.property("unselectColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unselectColumn") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::unselectColumn() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column));
    }
}

void QtScriptShell_QAccessibleTableInterface::unselectRow(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("unselectRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unselectRow") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleTableInterface::unselectRow() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row));
    }
}

