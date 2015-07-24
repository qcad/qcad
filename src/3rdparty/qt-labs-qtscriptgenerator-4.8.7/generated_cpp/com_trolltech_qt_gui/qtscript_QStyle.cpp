#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstyle.h>
#include <QVariant>
#include <qapplication.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QStyle.h"

static const char * const qtscript_QStyle_function_names[] = {
    "QStyle"
    // static
    , "alignedRect"
    , "sliderPositionFromValue"
    , "sliderValueFromPosition"
    , "visualAlignment"
    , "visualPos"
    , "visualRect"
    // prototype
    , "combinedLayoutSpacing"
    , "drawComplexControl"
    , "drawControl"
    , "drawItemPixmap"
    , "drawItemText"
    , "drawPrimitive"
    , "generatedIconPixmap"
    , "hitTestComplexControl"
    , "itemPixmapRect"
    , "layoutSpacing"
    , "pixelMetric"
    , "polish"
    , "proxy"
    , "sizeFromContents"
    , "standardIcon"
    , "standardPalette"
    , "standardPixmap"
    , "styleHint"
    , "subControlRect"
    , "subElementRect"
    , "unpolish"
    , "toString"
};

static const char * const qtscript_QStyle_function_signatures[] = {
    ""
    // static
    , "LayoutDirection direction, Alignment alignment, QSize size, QRect rectangle"
    , "int min, int max, int val, int space, bool upsideDown"
    , "int min, int max, int pos, int space, bool upsideDown"
    , "LayoutDirection direction, Alignment alignment"
    , "LayoutDirection direction, QRect boundingRect, QPoint logicalPos"
    , "LayoutDirection direction, QRect boundingRect, QRect logicalRect"
    // prototype
    , "ControlTypes controls1, ControlTypes controls2, Orientation orientation, QStyleOption option, QWidget widget"
    , "ComplexControl cc, QStyleOptionComplex opt, QPainter p, QWidget widget"
    , "ControlElement element, QStyleOption opt, QPainter p, QWidget w"
    , "QPainter painter, QRect rect, int alignment, QPixmap pixmap"
    , "QPainter painter, QRect rect, int flags, QPalette pal, bool enabled, String text, ColorRole textRole"
    , "PrimitiveElement pe, QStyleOption opt, QPainter p, QWidget w"
    , "Mode iconMode, QPixmap pixmap, QStyleOption opt"
    , "ComplexControl cc, QStyleOptionComplex opt, QPoint pt, QWidget widget"
    , "QRect r, int flags, QPixmap pixmap"
    , "ControlType control1, ControlType control2, Orientation orientation, QStyleOption option, QWidget widget"
    , "PixelMetric metric, QStyleOption option, QWidget widget"
    , "QApplication arg__1\nQPalette arg__1\nQWidget arg__1"
    , ""
    , "ContentsType ct, QStyleOption opt, QSize contentsSize, QWidget w"
    , "StandardPixmap standardIcon, QStyleOption option, QWidget widget"
    , ""
    , "StandardPixmap standardPixmap, QStyleOption opt, QWidget widget"
    , "StyleHint stylehint, QStyleOption opt, QWidget widget, QStyleHintReturn returnData"
    , "ComplexControl cc, QStyleOptionComplex opt, SubControl sc, QWidget widget"
    , "SubElement subElement, QStyleOption option, QWidget widget"
    , "QApplication arg__1\nQWidget arg__1"
""
};

static const int qtscript_QStyle_function_lengths[] = {
    0
    // static
    , 4
    , 5
    , 5
    , 2
    , 3
    , 3
    // prototype
    , 5
    , 4
    , 4
    , 4
    , 7
    , 4
    , 3
    , 4
    , 3
    , 5
    , 3
    , 1
    , 0
    , 4
    , 3
    , 0
    , 3
    , 4
    , 4
    , 3
    , 1
    , 0
};

static QScriptValue qtscript_QStyle_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyle::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyle*)
Q_DECLARE_METATYPE(QtScriptShell_QStyle*)
Q_DECLARE_METATYPE(QStyle::PixelMetric)
Q_DECLARE_METATYPE(QStyle::SubControl)
Q_DECLARE_METATYPE(QFlags<QStyle::SubControl>)
Q_DECLARE_METATYPE(QStyle::StandardPixmap)
Q_DECLARE_METATYPE(QStyle::StyleHint)
Q_DECLARE_METATYPE(QStyle::PrimitiveElement)
Q_DECLARE_METATYPE(QStyle::ControlElement)
Q_DECLARE_METATYPE(QStyle::ContentsType)
Q_DECLARE_METATYPE(QStyle::StateFlag)
Q_DECLARE_METATYPE(QFlags<QStyle::StateFlag>)
Q_DECLARE_METATYPE(QStyle::ComplexControl)
Q_DECLARE_METATYPE(QStyle::RequestSoftwareInputPanel)
Q_DECLARE_METATYPE(QStyle::SubElement)
Q_DECLARE_METATYPE(QFlags<QSizePolicy::ControlType>)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QStyleOption*)
Q_DECLARE_METATYPE(QStyleOptionComplex*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QPalette::ColorRole)
Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QSizePolicy::ControlType)
Q_DECLARE_METATYPE(QApplication*)
Q_DECLARE_METATYPE(QStyleHintReturn*)
Q_DECLARE_METATYPE(Qt::LayoutDirection)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QStyle::PixelMetric
//

static const QStyle::PixelMetric qtscript_QStyle_PixelMetric_values[] = {
    QStyle::PM_CustomBase
    , QStyle::PM_ButtonMargin
    , QStyle::PM_ButtonDefaultIndicator
    , QStyle::PM_MenuButtonIndicator
    , QStyle::PM_ButtonShiftHorizontal
    , QStyle::PM_ButtonShiftVertical
    , QStyle::PM_DefaultFrameWidth
    , QStyle::PM_SpinBoxFrameWidth
    , QStyle::PM_ComboBoxFrameWidth
    , QStyle::PM_MaximumDragDistance
    , QStyle::PM_ScrollBarExtent
    , QStyle::PM_ScrollBarSliderMin
    , QStyle::PM_SliderThickness
    , QStyle::PM_SliderControlThickness
    , QStyle::PM_SliderLength
    , QStyle::PM_SliderTickmarkOffset
    , QStyle::PM_SliderSpaceAvailable
    , QStyle::PM_DockWidgetSeparatorExtent
    , QStyle::PM_DockWidgetHandleExtent
    , QStyle::PM_DockWidgetFrameWidth
    , QStyle::PM_TabBarTabOverlap
    , QStyle::PM_TabBarTabHSpace
    , QStyle::PM_TabBarTabVSpace
    , QStyle::PM_TabBarBaseHeight
    , QStyle::PM_TabBarBaseOverlap
    , QStyle::PM_ProgressBarChunkWidth
    , QStyle::PM_SplitterWidth
    , QStyle::PM_TitleBarHeight
    , QStyle::PM_MenuScrollerHeight
    , QStyle::PM_MenuHMargin
    , QStyle::PM_MenuVMargin
    , QStyle::PM_MenuPanelWidth
    , QStyle::PM_MenuTearoffHeight
    , QStyle::PM_MenuDesktopFrameWidth
    , QStyle::PM_MenuBarPanelWidth
    , QStyle::PM_MenuBarItemSpacing
    , QStyle::PM_MenuBarVMargin
    , QStyle::PM_MenuBarHMargin
    , QStyle::PM_IndicatorWidth
    , QStyle::PM_IndicatorHeight
    , QStyle::PM_ExclusiveIndicatorWidth
    , QStyle::PM_ExclusiveIndicatorHeight
    , QStyle::PM_CheckListButtonSize
    , QStyle::PM_CheckListControllerSize
    , QStyle::PM_DialogButtonsSeparator
    , QStyle::PM_DialogButtonsButtonWidth
    , QStyle::PM_DialogButtonsButtonHeight
    , QStyle::PM_MdiSubWindowFrameWidth
    , QStyle::PM_MdiSubWindowMinimizedWidth
    , QStyle::PM_HeaderMargin
    , QStyle::PM_HeaderMarkSize
    , QStyle::PM_HeaderGripMargin
    , QStyle::PM_TabBarTabShiftHorizontal
    , QStyle::PM_TabBarTabShiftVertical
    , QStyle::PM_TabBarScrollButtonWidth
    , QStyle::PM_ToolBarFrameWidth
    , QStyle::PM_ToolBarHandleExtent
    , QStyle::PM_ToolBarItemSpacing
    , QStyle::PM_ToolBarItemMargin
    , QStyle::PM_ToolBarSeparatorExtent
    , QStyle::PM_ToolBarExtensionExtent
    , QStyle::PM_SpinBoxSliderHeight
    , QStyle::PM_DefaultTopLevelMargin
    , QStyle::PM_DefaultChildMargin
    , QStyle::PM_DefaultLayoutSpacing
    , QStyle::PM_ToolBarIconSize
    , QStyle::PM_ListViewIconSize
    , QStyle::PM_IconViewIconSize
    , QStyle::PM_SmallIconSize
    , QStyle::PM_LargeIconSize
    , QStyle::PM_FocusFrameVMargin
    , QStyle::PM_FocusFrameHMargin
    , QStyle::PM_ToolTipLabelFrameWidth
    , QStyle::PM_CheckBoxLabelSpacing
    , QStyle::PM_TabBarIconSize
    , QStyle::PM_SizeGripSize
    , QStyle::PM_DockWidgetTitleMargin
    , QStyle::PM_MessageBoxIconSize
    , QStyle::PM_ButtonIconSize
    , QStyle::PM_DockWidgetTitleBarButtonMargin
    , QStyle::PM_RadioButtonLabelSpacing
    , QStyle::PM_LayoutLeftMargin
    , QStyle::PM_LayoutTopMargin
    , QStyle::PM_LayoutRightMargin
    , QStyle::PM_LayoutBottomMargin
    , QStyle::PM_LayoutHorizontalSpacing
    , QStyle::PM_LayoutVerticalSpacing
    , QStyle::PM_TabBar_ScrollButtonOverlap
    , QStyle::PM_TextCursorWidth
    , QStyle::PM_TabCloseIndicatorWidth
    , QStyle::PM_TabCloseIndicatorHeight
    , QStyle::PM_ScrollView_ScrollBarSpacing
    , QStyle::PM_SubMenuOverlap
};

static const char * const qtscript_QStyle_PixelMetric_keys[] = {
    "PM_CustomBase"
    , "PM_ButtonMargin"
    , "PM_ButtonDefaultIndicator"
    , "PM_MenuButtonIndicator"
    , "PM_ButtonShiftHorizontal"
    , "PM_ButtonShiftVertical"
    , "PM_DefaultFrameWidth"
    , "PM_SpinBoxFrameWidth"
    , "PM_ComboBoxFrameWidth"
    , "PM_MaximumDragDistance"
    , "PM_ScrollBarExtent"
    , "PM_ScrollBarSliderMin"
    , "PM_SliderThickness"
    , "PM_SliderControlThickness"
    , "PM_SliderLength"
    , "PM_SliderTickmarkOffset"
    , "PM_SliderSpaceAvailable"
    , "PM_DockWidgetSeparatorExtent"
    , "PM_DockWidgetHandleExtent"
    , "PM_DockWidgetFrameWidth"
    , "PM_TabBarTabOverlap"
    , "PM_TabBarTabHSpace"
    , "PM_TabBarTabVSpace"
    , "PM_TabBarBaseHeight"
    , "PM_TabBarBaseOverlap"
    , "PM_ProgressBarChunkWidth"
    , "PM_SplitterWidth"
    , "PM_TitleBarHeight"
    , "PM_MenuScrollerHeight"
    , "PM_MenuHMargin"
    , "PM_MenuVMargin"
    , "PM_MenuPanelWidth"
    , "PM_MenuTearoffHeight"
    , "PM_MenuDesktopFrameWidth"
    , "PM_MenuBarPanelWidth"
    , "PM_MenuBarItemSpacing"
    , "PM_MenuBarVMargin"
    , "PM_MenuBarHMargin"
    , "PM_IndicatorWidth"
    , "PM_IndicatorHeight"
    , "PM_ExclusiveIndicatorWidth"
    , "PM_ExclusiveIndicatorHeight"
    , "PM_CheckListButtonSize"
    , "PM_CheckListControllerSize"
    , "PM_DialogButtonsSeparator"
    , "PM_DialogButtonsButtonWidth"
    , "PM_DialogButtonsButtonHeight"
    , "PM_MdiSubWindowFrameWidth"
    , "PM_MdiSubWindowMinimizedWidth"
    , "PM_HeaderMargin"
    , "PM_HeaderMarkSize"
    , "PM_HeaderGripMargin"
    , "PM_TabBarTabShiftHorizontal"
    , "PM_TabBarTabShiftVertical"
    , "PM_TabBarScrollButtonWidth"
    , "PM_ToolBarFrameWidth"
    , "PM_ToolBarHandleExtent"
    , "PM_ToolBarItemSpacing"
    , "PM_ToolBarItemMargin"
    , "PM_ToolBarSeparatorExtent"
    , "PM_ToolBarExtensionExtent"
    , "PM_SpinBoxSliderHeight"
    , "PM_DefaultTopLevelMargin"
    , "PM_DefaultChildMargin"
    , "PM_DefaultLayoutSpacing"
    , "PM_ToolBarIconSize"
    , "PM_ListViewIconSize"
    , "PM_IconViewIconSize"
    , "PM_SmallIconSize"
    , "PM_LargeIconSize"
    , "PM_FocusFrameVMargin"
    , "PM_FocusFrameHMargin"
    , "PM_ToolTipLabelFrameWidth"
    , "PM_CheckBoxLabelSpacing"
    , "PM_TabBarIconSize"
    , "PM_SizeGripSize"
    , "PM_DockWidgetTitleMargin"
    , "PM_MessageBoxIconSize"
    , "PM_ButtonIconSize"
    , "PM_DockWidgetTitleBarButtonMargin"
    , "PM_RadioButtonLabelSpacing"
    , "PM_LayoutLeftMargin"
    , "PM_LayoutTopMargin"
    , "PM_LayoutRightMargin"
    , "PM_LayoutBottomMargin"
    , "PM_LayoutHorizontalSpacing"
    , "PM_LayoutVerticalSpacing"
    , "PM_TabBar_ScrollButtonOverlap"
    , "PM_TextCursorWidth"
    , "PM_TabCloseIndicatorWidth"
    , "PM_TabCloseIndicatorHeight"
    , "PM_ScrollView_ScrollBarSpacing"
    , "PM_SubMenuOverlap"
};

static QString qtscript_QStyle_PixelMetric_toStringHelper(QStyle::PixelMetric value)
{
    for (int i = 0; i < 93; ++i) {
        if (qtscript_QStyle_PixelMetric_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_PixelMetric_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_PixelMetric_toScriptValue(QScriptEngine *engine, const QStyle::PixelMetric &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_PixelMetric_toStringHelper(value));
}

static void qtscript_QStyle_PixelMetric_fromScriptValue(const QScriptValue &value, QStyle::PixelMetric &out)
{
    out = qvariant_cast<QStyle::PixelMetric>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_PixelMetric(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 93; ++i) {
        if (qtscript_QStyle_PixelMetric_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::PixelMetric>(arg));
    }
    return context->throwError(QString::fromLatin1("PixelMetric(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_PixelMetric_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::PixelMetric value = qscriptvalue_cast<QStyle::PixelMetric>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_PixelMetric_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::PixelMetric value = qscriptvalue_cast<QStyle::PixelMetric>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_PixelMetric_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_PixelMetric_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_PixelMetric,
        qtscript_QStyle_PixelMetric_valueOf, qtscript_QStyle_PixelMetric_toString);
    qScriptRegisterMetaType<QStyle::PixelMetric>(engine, qtscript_QStyle_PixelMetric_toScriptValue,
        qtscript_QStyle_PixelMetric_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 93; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_PixelMetric_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_PixelMetric_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::SubControl
//

static const QStyle::SubControl qtscript_QStyle_SubControl_values[] = {
    QStyle::SC_CustomBase
    , QStyle::SC_All
    , QStyle::SC_None
    , QStyle::SC_ScrollBarAddLine
    , QStyle::SC_ScrollBarSubLine
    , QStyle::SC_ScrollBarAddPage
    , QStyle::SC_ScrollBarSubPage
    , QStyle::SC_ScrollBarFirst
    , QStyle::SC_ScrollBarLast
    , QStyle::SC_ScrollBarSlider
    , QStyle::SC_ScrollBarGroove
    , QStyle::SC_TitleBarLabel
};

static const char * const qtscript_QStyle_SubControl_keys[] = {
    "SC_CustomBase"
    , "SC_All"
    , "SC_None"
    , "SC_ScrollBarAddLine"
    , "SC_ScrollBarSubLine"
    , "SC_ScrollBarAddPage"
    , "SC_ScrollBarSubPage"
    , "SC_ScrollBarFirst"
    , "SC_ScrollBarLast"
    , "SC_ScrollBarSlider"
    , "SC_ScrollBarGroove"
    , "SC_TitleBarLabel"
};

static QString qtscript_QStyle_SubControl_toStringHelper(QStyle::SubControl value)
{
    for (int i = 0; i < 12; ++i) {
        if (qtscript_QStyle_SubControl_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_SubControl_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_SubControl_toScriptValue(QScriptEngine *engine, const QStyle::SubControl &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_SubControl_toStringHelper(value));
}

static void qtscript_QStyle_SubControl_fromScriptValue(const QScriptValue &value, QStyle::SubControl &out)
{
    out = qvariant_cast<QStyle::SubControl>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_SubControl(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 12; ++i) {
        if (qtscript_QStyle_SubControl_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::SubControl>(arg));
    }
    return context->throwError(QString::fromLatin1("SubControl(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_SubControl_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::SubControl value = qscriptvalue_cast<QStyle::SubControl>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_SubControl_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::SubControl value = qscriptvalue_cast<QStyle::SubControl>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_SubControl_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_SubControl_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_SubControl,
        qtscript_QStyle_SubControl_valueOf, qtscript_QStyle_SubControl_toString);
    qScriptRegisterMetaType<QStyle::SubControl>(engine, qtscript_QStyle_SubControl_toScriptValue,
        qtscript_QStyle_SubControl_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 12; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_SubControl_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_SubControl_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::SubControls
//

static QScriptValue qtscript_QStyle_SubControls_toScriptValue(QScriptEngine *engine, const QStyle::SubControls &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyle_SubControls_fromScriptValue(const QScriptValue &value, QStyle::SubControls &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyle::SubControls>())
        out = qvariant_cast<QStyle::SubControls>(var);
    else if (var.userType() == qMetaTypeId<QStyle::SubControl>())
        out = qvariant_cast<QStyle::SubControl>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyle_SubControls(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::SubControls result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyle::SubControls>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyle::SubControl>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("SubControls(): argument %0 is not of type SubControl").arg(i));
            }
            result |= qvariant_cast<QStyle::SubControl>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyle_SubControls_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::SubControls value = qscriptvalue_cast<QStyle::SubControls>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_SubControls_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::SubControls value = qscriptvalue_cast<QStyle::SubControls>(context->thisObject());
    QString result;
    for (int i = 0; i < 12; ++i) {
        if ((value & qtscript_QStyle_SubControl_values[i]) == qtscript_QStyle_SubControl_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyle_SubControl_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyle_SubControls_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyle::SubControls>() == otherObj.value<QStyle::SubControls>())));
}

static QScriptValue qtscript_create_QStyle_SubControls_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyle_SubControls, qtscript_QStyle_SubControls_valueOf,
        qtscript_QStyle_SubControls_toString, qtscript_QStyle_SubControls_equals);
    qScriptRegisterMetaType<QStyle::SubControls>(engine, qtscript_QStyle_SubControls_toScriptValue,
        qtscript_QStyle_SubControls_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyle::StandardPixmap
//

static const QStyle::StandardPixmap qtscript_QStyle_StandardPixmap_values[] = {
    QStyle::SP_CustomBase
    , QStyle::SP_TitleBarMenuButton
    , QStyle::SP_TitleBarMinButton
    , QStyle::SP_TitleBarMaxButton
    , QStyle::SP_TitleBarCloseButton
    , QStyle::SP_TitleBarNormalButton
    , QStyle::SP_TitleBarShadeButton
    , QStyle::SP_TitleBarUnshadeButton
    , QStyle::SP_TitleBarContextHelpButton
    , QStyle::SP_DockWidgetCloseButton
    , QStyle::SP_MessageBoxInformation
    , QStyle::SP_MessageBoxWarning
    , QStyle::SP_MessageBoxCritical
    , QStyle::SP_MessageBoxQuestion
    , QStyle::SP_DesktopIcon
    , QStyle::SP_TrashIcon
    , QStyle::SP_ComputerIcon
    , QStyle::SP_DriveFDIcon
    , QStyle::SP_DriveHDIcon
    , QStyle::SP_DriveCDIcon
    , QStyle::SP_DriveDVDIcon
    , QStyle::SP_DriveNetIcon
    , QStyle::SP_DirOpenIcon
    , QStyle::SP_DirClosedIcon
    , QStyle::SP_DirLinkIcon
    , QStyle::SP_FileIcon
    , QStyle::SP_FileLinkIcon
    , QStyle::SP_ToolBarHorizontalExtensionButton
    , QStyle::SP_ToolBarVerticalExtensionButton
    , QStyle::SP_FileDialogStart
    , QStyle::SP_FileDialogEnd
    , QStyle::SP_FileDialogToParent
    , QStyle::SP_FileDialogNewFolder
    , QStyle::SP_FileDialogDetailedView
    , QStyle::SP_FileDialogInfoView
    , QStyle::SP_FileDialogContentsView
    , QStyle::SP_FileDialogListView
    , QStyle::SP_FileDialogBack
    , QStyle::SP_DirIcon
    , QStyle::SP_DialogOkButton
    , QStyle::SP_DialogCancelButton
    , QStyle::SP_DialogHelpButton
    , QStyle::SP_DialogOpenButton
    , QStyle::SP_DialogSaveButton
    , QStyle::SP_DialogCloseButton
    , QStyle::SP_DialogApplyButton
    , QStyle::SP_DialogResetButton
    , QStyle::SP_DialogDiscardButton
    , QStyle::SP_DialogYesButton
    , QStyle::SP_DialogNoButton
    , QStyle::SP_ArrowUp
    , QStyle::SP_ArrowDown
    , QStyle::SP_ArrowLeft
    , QStyle::SP_ArrowRight
    , QStyle::SP_ArrowBack
    , QStyle::SP_ArrowForward
    , QStyle::SP_DirHomeIcon
    , QStyle::SP_CommandLink
    , QStyle::SP_VistaShield
    , QStyle::SP_BrowserReload
    , QStyle::SP_BrowserStop
    , QStyle::SP_MediaPlay
    , QStyle::SP_MediaStop
    , QStyle::SP_MediaPause
    , QStyle::SP_MediaSkipForward
    , QStyle::SP_MediaSkipBackward
    , QStyle::SP_MediaSeekForward
    , QStyle::SP_MediaSeekBackward
    , QStyle::SP_MediaVolume
    , QStyle::SP_MediaVolumeMuted
};

static const char * const qtscript_QStyle_StandardPixmap_keys[] = {
    "SP_CustomBase"
    , "SP_TitleBarMenuButton"
    , "SP_TitleBarMinButton"
    , "SP_TitleBarMaxButton"
    , "SP_TitleBarCloseButton"
    , "SP_TitleBarNormalButton"
    , "SP_TitleBarShadeButton"
    , "SP_TitleBarUnshadeButton"
    , "SP_TitleBarContextHelpButton"
    , "SP_DockWidgetCloseButton"
    , "SP_MessageBoxInformation"
    , "SP_MessageBoxWarning"
    , "SP_MessageBoxCritical"
    , "SP_MessageBoxQuestion"
    , "SP_DesktopIcon"
    , "SP_TrashIcon"
    , "SP_ComputerIcon"
    , "SP_DriveFDIcon"
    , "SP_DriveHDIcon"
    , "SP_DriveCDIcon"
    , "SP_DriveDVDIcon"
    , "SP_DriveNetIcon"
    , "SP_DirOpenIcon"
    , "SP_DirClosedIcon"
    , "SP_DirLinkIcon"
    , "SP_FileIcon"
    , "SP_FileLinkIcon"
    , "SP_ToolBarHorizontalExtensionButton"
    , "SP_ToolBarVerticalExtensionButton"
    , "SP_FileDialogStart"
    , "SP_FileDialogEnd"
    , "SP_FileDialogToParent"
    , "SP_FileDialogNewFolder"
    , "SP_FileDialogDetailedView"
    , "SP_FileDialogInfoView"
    , "SP_FileDialogContentsView"
    , "SP_FileDialogListView"
    , "SP_FileDialogBack"
    , "SP_DirIcon"
    , "SP_DialogOkButton"
    , "SP_DialogCancelButton"
    , "SP_DialogHelpButton"
    , "SP_DialogOpenButton"
    , "SP_DialogSaveButton"
    , "SP_DialogCloseButton"
    , "SP_DialogApplyButton"
    , "SP_DialogResetButton"
    , "SP_DialogDiscardButton"
    , "SP_DialogYesButton"
    , "SP_DialogNoButton"
    , "SP_ArrowUp"
    , "SP_ArrowDown"
    , "SP_ArrowLeft"
    , "SP_ArrowRight"
    , "SP_ArrowBack"
    , "SP_ArrowForward"
    , "SP_DirHomeIcon"
    , "SP_CommandLink"
    , "SP_VistaShield"
    , "SP_BrowserReload"
    , "SP_BrowserStop"
    , "SP_MediaPlay"
    , "SP_MediaStop"
    , "SP_MediaPause"
    , "SP_MediaSkipForward"
    , "SP_MediaSkipBackward"
    , "SP_MediaSeekForward"
    , "SP_MediaSeekBackward"
    , "SP_MediaVolume"
    , "SP_MediaVolumeMuted"
};

static QString qtscript_QStyle_StandardPixmap_toStringHelper(QStyle::StandardPixmap value)
{
    for (int i = 0; i < 70; ++i) {
        if (qtscript_QStyle_StandardPixmap_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_StandardPixmap_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_StandardPixmap_toScriptValue(QScriptEngine *engine, const QStyle::StandardPixmap &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_StandardPixmap_toStringHelper(value));
}

static void qtscript_QStyle_StandardPixmap_fromScriptValue(const QScriptValue &value, QStyle::StandardPixmap &out)
{
    out = qvariant_cast<QStyle::StandardPixmap>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_StandardPixmap(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 70; ++i) {
        if (qtscript_QStyle_StandardPixmap_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::StandardPixmap>(arg));
    }
    return context->throwError(QString::fromLatin1("StandardPixmap(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_StandardPixmap_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::StandardPixmap value = qscriptvalue_cast<QStyle::StandardPixmap>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_StandardPixmap_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::StandardPixmap value = qscriptvalue_cast<QStyle::StandardPixmap>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_StandardPixmap_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_StandardPixmap_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_StandardPixmap,
        qtscript_QStyle_StandardPixmap_valueOf, qtscript_QStyle_StandardPixmap_toString);
    qScriptRegisterMetaType<QStyle::StandardPixmap>(engine, qtscript_QStyle_StandardPixmap_toScriptValue,
        qtscript_QStyle_StandardPixmap_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 70; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_StandardPixmap_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_StandardPixmap_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::StyleHint
//

static const QStyle::StyleHint qtscript_QStyle_StyleHint_values[] = {
    QStyle::SH_CustomBase
    , QStyle::SH_EtchDisabledText
    , QStyle::SH_DitherDisabledText
    , QStyle::SH_ScrollBar_MiddleClickAbsolutePosition
    , QStyle::SH_ScrollBar_ScrollWhenPointerLeavesControl
    , QStyle::SH_TabBar_SelectMouseType
    , QStyle::SH_TabBar_Alignment
    , QStyle::SH_Header_ArrowAlignment
    , QStyle::SH_Slider_SnapToValue
    , QStyle::SH_Slider_SloppyKeyEvents
    , QStyle::SH_ProgressDialog_CenterCancelButton
    , QStyle::SH_ProgressDialog_TextLabelAlignment
    , QStyle::SH_PrintDialog_RightAlignButtons
    , QStyle::SH_MainWindow_SpaceBelowMenuBar
    , QStyle::SH_FontDialog_SelectAssociatedText
    , QStyle::SH_Menu_AllowActiveAndDisabled
    , QStyle::SH_Menu_SpaceActivatesItem
    , QStyle::SH_Menu_SubMenuPopupDelay
    , QStyle::SH_ScrollView_FrameOnlyAroundContents
    , QStyle::SH_MenuBar_AltKeyNavigation
    , QStyle::SH_ComboBox_ListMouseTracking
    , QStyle::SH_Menu_MouseTracking
    , QStyle::SH_MenuBar_MouseTracking
    , QStyle::SH_ItemView_ChangeHighlightOnFocus
    , QStyle::SH_Widget_ShareActivation
    , QStyle::SH_Workspace_FillSpaceOnMaximize
    , QStyle::SH_ComboBox_Popup
    , QStyle::SH_TitleBar_NoBorder
    , QStyle::SH_Slider_StopMouseOverSlider
    , QStyle::SH_BlinkCursorWhenTextSelected
    , QStyle::SH_RichText_FullWidthSelection
    , QStyle::SH_Menu_Scrollable
    , QStyle::SH_GroupBox_TextLabelVerticalAlignment
    , QStyle::SH_GroupBox_TextLabelColor
    , QStyle::SH_Menu_SloppySubMenus
    , QStyle::SH_Table_GridLineColor
    , QStyle::SH_LineEdit_PasswordCharacter
    , QStyle::SH_DialogButtons_DefaultButton
    , QStyle::SH_ToolBox_SelectedPageTitleBold
    , QStyle::SH_TabBar_PreferNoArrows
    , QStyle::SH_ScrollBar_LeftClickAbsolutePosition
    , QStyle::SH_Q3ListViewExpand_SelectMouseType
    , QStyle::SH_UnderlineShortcut
    , QStyle::SH_SpinBox_AnimateButton
    , QStyle::SH_SpinBox_KeyPressAutoRepeatRate
    , QStyle::SH_SpinBox_ClickAutoRepeatRate
    , QStyle::SH_Menu_FillScreenWithScroll
    , QStyle::SH_ToolTipLabel_Opacity
    , QStyle::SH_DrawMenuBarSeparator
    , QStyle::SH_TitleBar_ModifyNotification
    , QStyle::SH_Button_FocusPolicy
    , QStyle::SH_MenuBar_DismissOnSecondClick
    , QStyle::SH_MessageBox_UseBorderForButtonSpacing
    , QStyle::SH_TitleBar_AutoRaise
    , QStyle::SH_ToolButton_PopupDelay
    , QStyle::SH_FocusFrame_Mask
    , QStyle::SH_RubberBand_Mask
    , QStyle::SH_WindowFrame_Mask
    , QStyle::SH_SpinControls_DisableOnBounds
    , QStyle::SH_Dial_BackgroundRole
    , QStyle::SH_ComboBox_LayoutDirection
    , QStyle::SH_ItemView_EllipsisLocation
    , QStyle::SH_ItemView_ShowDecorationSelected
    , QStyle::SH_ItemView_ActivateItemOnSingleClick
    , QStyle::SH_ScrollBar_ContextMenu
    , QStyle::SH_ScrollBar_RollBetweenButtons
    , QStyle::SH_Slider_AbsoluteSetButtons
    , QStyle::SH_Slider_PageSetButtons
    , QStyle::SH_Menu_KeyboardSearch
    , QStyle::SH_TabBar_ElideMode
    , QStyle::SH_DialogButtonLayout
    , QStyle::SH_ComboBox_PopupFrameStyle
    , QStyle::SH_MessageBox_TextInteractionFlags
    , QStyle::SH_DialogButtonBox_ButtonsHaveIcons
    , QStyle::SH_SpellCheckUnderlineStyle
    , QStyle::SH_MessageBox_CenterButtons
    , QStyle::SH_Menu_SelectionWrap
    , QStyle::SH_ItemView_MovementWithoutUpdatingSelection
    , QStyle::SH_ToolTip_Mask
    , QStyle::SH_FocusFrame_AboveWidget
    , QStyle::SH_TextControl_FocusIndicatorTextCharFormat
    , QStyle::SH_WizardStyle
    , QStyle::SH_ItemView_ArrowKeysNavigateIntoChildren
    , QStyle::SH_Menu_Mask
    , QStyle::SH_Menu_FlashTriggeredItem
    , QStyle::SH_Menu_FadeOutOnHide
    , QStyle::SH_SpinBox_ClickAutoRepeatThreshold
    , QStyle::SH_ItemView_PaintAlternatingRowColorsForEmptyArea
    , QStyle::SH_FormLayoutWrapPolicy
    , QStyle::SH_TabWidget_DefaultTabPosition
    , QStyle::SH_ToolBar_Movable
    , QStyle::SH_FormLayoutFieldGrowthPolicy
    , QStyle::SH_FormLayoutFormAlignment
    , QStyle::SH_FormLayoutLabelAlignment
    , QStyle::SH_ItemView_DrawDelegateFrame
    , QStyle::SH_TabBar_CloseButtonPosition
    , QStyle::SH_DockWidget_ButtonsHaveFrame
    , QStyle::SH_ToolButtonStyle
    , QStyle::SH_RequestSoftwareInputPanel
};

static const char * const qtscript_QStyle_StyleHint_keys[] = {
    "SH_CustomBase"
    , "SH_EtchDisabledText"
    , "SH_DitherDisabledText"
    , "SH_ScrollBar_MiddleClickAbsolutePosition"
    , "SH_ScrollBar_ScrollWhenPointerLeavesControl"
    , "SH_TabBar_SelectMouseType"
    , "SH_TabBar_Alignment"
    , "SH_Header_ArrowAlignment"
    , "SH_Slider_SnapToValue"
    , "SH_Slider_SloppyKeyEvents"
    , "SH_ProgressDialog_CenterCancelButton"
    , "SH_ProgressDialog_TextLabelAlignment"
    , "SH_PrintDialog_RightAlignButtons"
    , "SH_MainWindow_SpaceBelowMenuBar"
    , "SH_FontDialog_SelectAssociatedText"
    , "SH_Menu_AllowActiveAndDisabled"
    , "SH_Menu_SpaceActivatesItem"
    , "SH_Menu_SubMenuPopupDelay"
    , "SH_ScrollView_FrameOnlyAroundContents"
    , "SH_MenuBar_AltKeyNavigation"
    , "SH_ComboBox_ListMouseTracking"
    , "SH_Menu_MouseTracking"
    , "SH_MenuBar_MouseTracking"
    , "SH_ItemView_ChangeHighlightOnFocus"
    , "SH_Widget_ShareActivation"
    , "SH_Workspace_FillSpaceOnMaximize"
    , "SH_ComboBox_Popup"
    , "SH_TitleBar_NoBorder"
    , "SH_Slider_StopMouseOverSlider"
    , "SH_BlinkCursorWhenTextSelected"
    , "SH_RichText_FullWidthSelection"
    , "SH_Menu_Scrollable"
    , "SH_GroupBox_TextLabelVerticalAlignment"
    , "SH_GroupBox_TextLabelColor"
    , "SH_Menu_SloppySubMenus"
    , "SH_Table_GridLineColor"
    , "SH_LineEdit_PasswordCharacter"
    , "SH_DialogButtons_DefaultButton"
    , "SH_ToolBox_SelectedPageTitleBold"
    , "SH_TabBar_PreferNoArrows"
    , "SH_ScrollBar_LeftClickAbsolutePosition"
    , "SH_Q3ListViewExpand_SelectMouseType"
    , "SH_UnderlineShortcut"
    , "SH_SpinBox_AnimateButton"
    , "SH_SpinBox_KeyPressAutoRepeatRate"
    , "SH_SpinBox_ClickAutoRepeatRate"
    , "SH_Menu_FillScreenWithScroll"
    , "SH_ToolTipLabel_Opacity"
    , "SH_DrawMenuBarSeparator"
    , "SH_TitleBar_ModifyNotification"
    , "SH_Button_FocusPolicy"
    , "SH_MenuBar_DismissOnSecondClick"
    , "SH_MessageBox_UseBorderForButtonSpacing"
    , "SH_TitleBar_AutoRaise"
    , "SH_ToolButton_PopupDelay"
    , "SH_FocusFrame_Mask"
    , "SH_RubberBand_Mask"
    , "SH_WindowFrame_Mask"
    , "SH_SpinControls_DisableOnBounds"
    , "SH_Dial_BackgroundRole"
    , "SH_ComboBox_LayoutDirection"
    , "SH_ItemView_EllipsisLocation"
    , "SH_ItemView_ShowDecorationSelected"
    , "SH_ItemView_ActivateItemOnSingleClick"
    , "SH_ScrollBar_ContextMenu"
    , "SH_ScrollBar_RollBetweenButtons"
    , "SH_Slider_AbsoluteSetButtons"
    , "SH_Slider_PageSetButtons"
    , "SH_Menu_KeyboardSearch"
    , "SH_TabBar_ElideMode"
    , "SH_DialogButtonLayout"
    , "SH_ComboBox_PopupFrameStyle"
    , "SH_MessageBox_TextInteractionFlags"
    , "SH_DialogButtonBox_ButtonsHaveIcons"
    , "SH_SpellCheckUnderlineStyle"
    , "SH_MessageBox_CenterButtons"
    , "SH_Menu_SelectionWrap"
    , "SH_ItemView_MovementWithoutUpdatingSelection"
    , "SH_ToolTip_Mask"
    , "SH_FocusFrame_AboveWidget"
    , "SH_TextControl_FocusIndicatorTextCharFormat"
    , "SH_WizardStyle"
    , "SH_ItemView_ArrowKeysNavigateIntoChildren"
    , "SH_Menu_Mask"
    , "SH_Menu_FlashTriggeredItem"
    , "SH_Menu_FadeOutOnHide"
    , "SH_SpinBox_ClickAutoRepeatThreshold"
    , "SH_ItemView_PaintAlternatingRowColorsForEmptyArea"
    , "SH_FormLayoutWrapPolicy"
    , "SH_TabWidget_DefaultTabPosition"
    , "SH_ToolBar_Movable"
    , "SH_FormLayoutFieldGrowthPolicy"
    , "SH_FormLayoutFormAlignment"
    , "SH_FormLayoutLabelAlignment"
    , "SH_ItemView_DrawDelegateFrame"
    , "SH_TabBar_CloseButtonPosition"
    , "SH_DockWidget_ButtonsHaveFrame"
    , "SH_ToolButtonStyle"
    , "SH_RequestSoftwareInputPanel"
};

static QString qtscript_QStyle_StyleHint_toStringHelper(QStyle::StyleHint value)
{
    for (int i = 0; i < 99; ++i) {
        if (qtscript_QStyle_StyleHint_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_StyleHint_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_StyleHint_toScriptValue(QScriptEngine *engine, const QStyle::StyleHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_StyleHint_toStringHelper(value));
}

static void qtscript_QStyle_StyleHint_fromScriptValue(const QScriptValue &value, QStyle::StyleHint &out)
{
    out = qvariant_cast<QStyle::StyleHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_StyleHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 99; ++i) {
        if (qtscript_QStyle_StyleHint_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::StyleHint>(arg));
    }
    return context->throwError(QString::fromLatin1("StyleHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_StyleHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::StyleHint value = qscriptvalue_cast<QStyle::StyleHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_StyleHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::StyleHint value = qscriptvalue_cast<QStyle::StyleHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_StyleHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_StyleHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_StyleHint,
        qtscript_QStyle_StyleHint_valueOf, qtscript_QStyle_StyleHint_toString);
    qScriptRegisterMetaType<QStyle::StyleHint>(engine, qtscript_QStyle_StyleHint_toScriptValue,
        qtscript_QStyle_StyleHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 99; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_StyleHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_StyleHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::PrimitiveElement
//

static const QStyle::PrimitiveElement qtscript_QStyle_PrimitiveElement_values[] = {
    QStyle::PE_Q3CheckListController
    , QStyle::PE_Q3CheckListExclusiveIndicator
    , QStyle::PE_Q3CheckListIndicator
    , QStyle::PE_Q3DockWindowSeparator
    , QStyle::PE_Q3Separator
    , QStyle::PE_Frame
    , QStyle::PE_FrameDefaultButton
    , QStyle::PE_FrameDockWidget
    , QStyle::PE_FrameFocusRect
    , QStyle::PE_FrameGroupBox
    , QStyle::PE_FrameLineEdit
    , QStyle::PE_FrameMenu
    , QStyle::PE_FrameStatusBar
    , QStyle::PE_FrameTabWidget
    , QStyle::PE_FrameWindow
    , QStyle::PE_FrameButtonBevel
    , QStyle::PE_FrameButtonTool
    , QStyle::PE_FrameTabBarBase
    , QStyle::PE_PanelButtonCommand
    , QStyle::PE_PanelButtonBevel
    , QStyle::PE_PanelButtonTool
    , QStyle::PE_PanelMenuBar
    , QStyle::PE_PanelToolBar
    , QStyle::PE_PanelLineEdit
    , QStyle::PE_IndicatorArrowDown
    , QStyle::PE_IndicatorArrowLeft
    , QStyle::PE_IndicatorArrowRight
    , QStyle::PE_IndicatorArrowUp
    , QStyle::PE_IndicatorBranch
    , QStyle::PE_IndicatorButtonDropDown
    , QStyle::PE_IndicatorViewItemCheck
    , QStyle::PE_IndicatorCheckBox
    , QStyle::PE_IndicatorDockWidgetResizeHandle
    , QStyle::PE_IndicatorHeaderArrow
    , QStyle::PE_IndicatorMenuCheckMark
    , QStyle::PE_IndicatorProgressChunk
    , QStyle::PE_IndicatorRadioButton
    , QStyle::PE_IndicatorSpinDown
    , QStyle::PE_IndicatorSpinMinus
    , QStyle::PE_IndicatorSpinPlus
    , QStyle::PE_IndicatorSpinUp
    , QStyle::PE_IndicatorToolBarHandle
    , QStyle::PE_IndicatorToolBarSeparator
    , QStyle::PE_PanelTipLabel
    , QStyle::PE_IndicatorTabTear
    , QStyle::PE_PanelScrollAreaCorner
    , QStyle::PE_Widget
    , QStyle::PE_IndicatorColumnViewArrow
    , QStyle::PE_IndicatorItemViewItemDrop
    , QStyle::PE_PanelItemViewItem
    , QStyle::PE_PanelItemViewRow
    , QStyle::PE_PanelStatusBar
    , QStyle::PE_IndicatorTabClose
    , QStyle::PE_PanelMenu
    , QStyle::PE_CustomBase
};

static const char * const qtscript_QStyle_PrimitiveElement_keys[] = {
    "PE_Q3CheckListController"
    , "PE_Q3CheckListExclusiveIndicator"
    , "PE_Q3CheckListIndicator"
    , "PE_Q3DockWindowSeparator"
    , "PE_Q3Separator"
    , "PE_Frame"
    , "PE_FrameDefaultButton"
    , "PE_FrameDockWidget"
    , "PE_FrameFocusRect"
    , "PE_FrameGroupBox"
    , "PE_FrameLineEdit"
    , "PE_FrameMenu"
    , "PE_FrameStatusBar"
    , "PE_FrameTabWidget"
    , "PE_FrameWindow"
    , "PE_FrameButtonBevel"
    , "PE_FrameButtonTool"
    , "PE_FrameTabBarBase"
    , "PE_PanelButtonCommand"
    , "PE_PanelButtonBevel"
    , "PE_PanelButtonTool"
    , "PE_PanelMenuBar"
    , "PE_PanelToolBar"
    , "PE_PanelLineEdit"
    , "PE_IndicatorArrowDown"
    , "PE_IndicatorArrowLeft"
    , "PE_IndicatorArrowRight"
    , "PE_IndicatorArrowUp"
    , "PE_IndicatorBranch"
    , "PE_IndicatorButtonDropDown"
    , "PE_IndicatorViewItemCheck"
    , "PE_IndicatorCheckBox"
    , "PE_IndicatorDockWidgetResizeHandle"
    , "PE_IndicatorHeaderArrow"
    , "PE_IndicatorMenuCheckMark"
    , "PE_IndicatorProgressChunk"
    , "PE_IndicatorRadioButton"
    , "PE_IndicatorSpinDown"
    , "PE_IndicatorSpinMinus"
    , "PE_IndicatorSpinPlus"
    , "PE_IndicatorSpinUp"
    , "PE_IndicatorToolBarHandle"
    , "PE_IndicatorToolBarSeparator"
    , "PE_PanelTipLabel"
    , "PE_IndicatorTabTear"
    , "PE_PanelScrollAreaCorner"
    , "PE_Widget"
    , "PE_IndicatorColumnViewArrow"
    , "PE_IndicatorItemViewItemDrop"
    , "PE_PanelItemViewItem"
    , "PE_PanelItemViewRow"
    , "PE_PanelStatusBar"
    , "PE_IndicatorTabClose"
    , "PE_PanelMenu"
    , "PE_CustomBase"
};

static QString qtscript_QStyle_PrimitiveElement_toStringHelper(QStyle::PrimitiveElement value)
{
    for (int i = 0; i < 55; ++i) {
        if (qtscript_QStyle_PrimitiveElement_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_PrimitiveElement_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_PrimitiveElement_toScriptValue(QScriptEngine *engine, const QStyle::PrimitiveElement &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_PrimitiveElement_toStringHelper(value));
}

static void qtscript_QStyle_PrimitiveElement_fromScriptValue(const QScriptValue &value, QStyle::PrimitiveElement &out)
{
    out = qvariant_cast<QStyle::PrimitiveElement>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_PrimitiveElement(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 55; ++i) {
        if (qtscript_QStyle_PrimitiveElement_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::PrimitiveElement>(arg));
    }
    return context->throwError(QString::fromLatin1("PrimitiveElement(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_PrimitiveElement_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::PrimitiveElement value = qscriptvalue_cast<QStyle::PrimitiveElement>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_PrimitiveElement_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::PrimitiveElement value = qscriptvalue_cast<QStyle::PrimitiveElement>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_PrimitiveElement_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_PrimitiveElement_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_PrimitiveElement,
        qtscript_QStyle_PrimitiveElement_valueOf, qtscript_QStyle_PrimitiveElement_toString);
    qScriptRegisterMetaType<QStyle::PrimitiveElement>(engine, qtscript_QStyle_PrimitiveElement_toScriptValue,
        qtscript_QStyle_PrimitiveElement_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 55; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_PrimitiveElement_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_PrimitiveElement_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::ControlElement
//

static const QStyle::ControlElement qtscript_QStyle_ControlElement_values[] = {
    QStyle::CE_CustomBase
    , QStyle::CE_PushButton
    , QStyle::CE_PushButtonBevel
    , QStyle::CE_PushButtonLabel
    , QStyle::CE_CheckBox
    , QStyle::CE_CheckBoxLabel
    , QStyle::CE_RadioButton
    , QStyle::CE_RadioButtonLabel
    , QStyle::CE_TabBarTab
    , QStyle::CE_TabBarTabShape
    , QStyle::CE_TabBarTabLabel
    , QStyle::CE_ProgressBar
    , QStyle::CE_ProgressBarGroove
    , QStyle::CE_ProgressBarContents
    , QStyle::CE_ProgressBarLabel
    , QStyle::CE_MenuItem
    , QStyle::CE_MenuScroller
    , QStyle::CE_MenuVMargin
    , QStyle::CE_MenuHMargin
    , QStyle::CE_MenuTearoff
    , QStyle::CE_MenuEmptyArea
    , QStyle::CE_MenuBarItem
    , QStyle::CE_MenuBarEmptyArea
    , QStyle::CE_ToolButtonLabel
    , QStyle::CE_Header
    , QStyle::CE_HeaderSection
    , QStyle::CE_HeaderLabel
    , QStyle::CE_Q3DockWindowEmptyArea
    , QStyle::CE_ToolBoxTab
    , QStyle::CE_SizeGrip
    , QStyle::CE_Splitter
    , QStyle::CE_RubberBand
    , QStyle::CE_DockWidgetTitle
    , QStyle::CE_ScrollBarAddLine
    , QStyle::CE_ScrollBarSubLine
    , QStyle::CE_ScrollBarAddPage
    , QStyle::CE_ScrollBarSubPage
    , QStyle::CE_ScrollBarSlider
    , QStyle::CE_ScrollBarFirst
    , QStyle::CE_ScrollBarLast
    , QStyle::CE_FocusFrame
    , QStyle::CE_ComboBoxLabel
    , QStyle::CE_ToolBar
    , QStyle::CE_ToolBoxTabShape
    , QStyle::CE_ToolBoxTabLabel
    , QStyle::CE_HeaderEmptyArea
    , QStyle::CE_ColumnViewGrip
    , QStyle::CE_ItemViewItem
    , QStyle::CE_ShapedFrame
};

static const char * const qtscript_QStyle_ControlElement_keys[] = {
    "CE_CustomBase"
    , "CE_PushButton"
    , "CE_PushButtonBevel"
    , "CE_PushButtonLabel"
    , "CE_CheckBox"
    , "CE_CheckBoxLabel"
    , "CE_RadioButton"
    , "CE_RadioButtonLabel"
    , "CE_TabBarTab"
    , "CE_TabBarTabShape"
    , "CE_TabBarTabLabel"
    , "CE_ProgressBar"
    , "CE_ProgressBarGroove"
    , "CE_ProgressBarContents"
    , "CE_ProgressBarLabel"
    , "CE_MenuItem"
    , "CE_MenuScroller"
    , "CE_MenuVMargin"
    , "CE_MenuHMargin"
    , "CE_MenuTearoff"
    , "CE_MenuEmptyArea"
    , "CE_MenuBarItem"
    , "CE_MenuBarEmptyArea"
    , "CE_ToolButtonLabel"
    , "CE_Header"
    , "CE_HeaderSection"
    , "CE_HeaderLabel"
    , "CE_Q3DockWindowEmptyArea"
    , "CE_ToolBoxTab"
    , "CE_SizeGrip"
    , "CE_Splitter"
    , "CE_RubberBand"
    , "CE_DockWidgetTitle"
    , "CE_ScrollBarAddLine"
    , "CE_ScrollBarSubLine"
    , "CE_ScrollBarAddPage"
    , "CE_ScrollBarSubPage"
    , "CE_ScrollBarSlider"
    , "CE_ScrollBarFirst"
    , "CE_ScrollBarLast"
    , "CE_FocusFrame"
    , "CE_ComboBoxLabel"
    , "CE_ToolBar"
    , "CE_ToolBoxTabShape"
    , "CE_ToolBoxTabLabel"
    , "CE_HeaderEmptyArea"
    , "CE_ColumnViewGrip"
    , "CE_ItemViewItem"
    , "CE_ShapedFrame"
};

static QString qtscript_QStyle_ControlElement_toStringHelper(QStyle::ControlElement value)
{
    for (int i = 0; i < 49; ++i) {
        if (qtscript_QStyle_ControlElement_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_ControlElement_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_ControlElement_toScriptValue(QScriptEngine *engine, const QStyle::ControlElement &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_ControlElement_toStringHelper(value));
}

static void qtscript_QStyle_ControlElement_fromScriptValue(const QScriptValue &value, QStyle::ControlElement &out)
{
    out = qvariant_cast<QStyle::ControlElement>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_ControlElement(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 49; ++i) {
        if (qtscript_QStyle_ControlElement_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::ControlElement>(arg));
    }
    return context->throwError(QString::fromLatin1("ControlElement(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_ControlElement_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::ControlElement value = qscriptvalue_cast<QStyle::ControlElement>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_ControlElement_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::ControlElement value = qscriptvalue_cast<QStyle::ControlElement>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_ControlElement_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_ControlElement_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_ControlElement,
        qtscript_QStyle_ControlElement_valueOf, qtscript_QStyle_ControlElement_toString);
    qScriptRegisterMetaType<QStyle::ControlElement>(engine, qtscript_QStyle_ControlElement_toScriptValue,
        qtscript_QStyle_ControlElement_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 49; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_ControlElement_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_ControlElement_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::ContentsType
//

static const QStyle::ContentsType qtscript_QStyle_ContentsType_values[] = {
    QStyle::CT_CustomBase
    , QStyle::CT_PushButton
    , QStyle::CT_CheckBox
    , QStyle::CT_RadioButton
    , QStyle::CT_ToolButton
    , QStyle::CT_ComboBox
    , QStyle::CT_Splitter
    , QStyle::CT_Q3DockWindow
    , QStyle::CT_ProgressBar
    , QStyle::CT_MenuItem
    , QStyle::CT_MenuBarItem
    , QStyle::CT_MenuBar
    , QStyle::CT_Menu
    , QStyle::CT_TabBarTab
    , QStyle::CT_Slider
    , QStyle::CT_ScrollBar
    , QStyle::CT_Q3Header
    , QStyle::CT_LineEdit
    , QStyle::CT_SpinBox
    , QStyle::CT_SizeGrip
    , QStyle::CT_TabWidget
    , QStyle::CT_DialogButtons
    , QStyle::CT_HeaderSection
    , QStyle::CT_GroupBox
    , QStyle::CT_MdiControls
    , QStyle::CT_ItemViewItem
};

static const char * const qtscript_QStyle_ContentsType_keys[] = {
    "CT_CustomBase"
    , "CT_PushButton"
    , "CT_CheckBox"
    , "CT_RadioButton"
    , "CT_ToolButton"
    , "CT_ComboBox"
    , "CT_Splitter"
    , "CT_Q3DockWindow"
    , "CT_ProgressBar"
    , "CT_MenuItem"
    , "CT_MenuBarItem"
    , "CT_MenuBar"
    , "CT_Menu"
    , "CT_TabBarTab"
    , "CT_Slider"
    , "CT_ScrollBar"
    , "CT_Q3Header"
    , "CT_LineEdit"
    , "CT_SpinBox"
    , "CT_SizeGrip"
    , "CT_TabWidget"
    , "CT_DialogButtons"
    , "CT_HeaderSection"
    , "CT_GroupBox"
    , "CT_MdiControls"
    , "CT_ItemViewItem"
};

static QString qtscript_QStyle_ContentsType_toStringHelper(QStyle::ContentsType value)
{
    for (int i = 0; i < 26; ++i) {
        if (qtscript_QStyle_ContentsType_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_ContentsType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_ContentsType_toScriptValue(QScriptEngine *engine, const QStyle::ContentsType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_ContentsType_toStringHelper(value));
}

static void qtscript_QStyle_ContentsType_fromScriptValue(const QScriptValue &value, QStyle::ContentsType &out)
{
    out = qvariant_cast<QStyle::ContentsType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_ContentsType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 26; ++i) {
        if (qtscript_QStyle_ContentsType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::ContentsType>(arg));
    }
    return context->throwError(QString::fromLatin1("ContentsType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_ContentsType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::ContentsType value = qscriptvalue_cast<QStyle::ContentsType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_ContentsType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::ContentsType value = qscriptvalue_cast<QStyle::ContentsType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_ContentsType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_ContentsType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_ContentsType,
        qtscript_QStyle_ContentsType_valueOf, qtscript_QStyle_ContentsType_toString);
    qScriptRegisterMetaType<QStyle::ContentsType>(engine, qtscript_QStyle_ContentsType_toScriptValue,
        qtscript_QStyle_ContentsType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 26; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_ContentsType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_ContentsType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::StateFlag
//

static const QStyle::StateFlag qtscript_QStyle_StateFlag_values[] = {
    QStyle::State_None
    , QStyle::State_Enabled
    , QStyle::State_Raised
    , QStyle::State_Sunken
    , QStyle::State_Off
    , QStyle::State_NoChange
    , QStyle::State_On
    , QStyle::State_DownArrow
    , QStyle::State_Horizontal
    , QStyle::State_HasFocus
    , QStyle::State_Top
    , QStyle::State_Bottom
    , QStyle::State_FocusAtBorder
    , QStyle::State_AutoRaise
    , QStyle::State_MouseOver
    , QStyle::State_UpArrow
    , QStyle::State_Selected
    , QStyle::State_Active
    , QStyle::State_Window
    , QStyle::State_Open
    , QStyle::State_Children
    , QStyle::State_Item
    , QStyle::State_Sibling
    , QStyle::State_Editing
    , QStyle::State_KeyboardFocusChange
    , QStyle::State_ReadOnly
    , QStyle::State_Small
    , QStyle::State_Mini
};

static const char * const qtscript_QStyle_StateFlag_keys[] = {
    "State_None"
    , "State_Enabled"
    , "State_Raised"
    , "State_Sunken"
    , "State_Off"
    , "State_NoChange"
    , "State_On"
    , "State_DownArrow"
    , "State_Horizontal"
    , "State_HasFocus"
    , "State_Top"
    , "State_Bottom"
    , "State_FocusAtBorder"
    , "State_AutoRaise"
    , "State_MouseOver"
    , "State_UpArrow"
    , "State_Selected"
    , "State_Active"
    , "State_Window"
    , "State_Open"
    , "State_Children"
    , "State_Item"
    , "State_Sibling"
    , "State_Editing"
    , "State_KeyboardFocusChange"
    , "State_ReadOnly"
    , "State_Small"
    , "State_Mini"
};

static QString qtscript_QStyle_StateFlag_toStringHelper(QStyle::StateFlag value)
{
    for (int i = 0; i < 28; ++i) {
        if (qtscript_QStyle_StateFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_StateFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_StateFlag_toScriptValue(QScriptEngine *engine, const QStyle::StateFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_StateFlag_toStringHelper(value));
}

static void qtscript_QStyle_StateFlag_fromScriptValue(const QScriptValue &value, QStyle::StateFlag &out)
{
    out = qvariant_cast<QStyle::StateFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_StateFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 28; ++i) {
        if (qtscript_QStyle_StateFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::StateFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("StateFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_StateFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::StateFlag value = qscriptvalue_cast<QStyle::StateFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_StateFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::StateFlag value = qscriptvalue_cast<QStyle::StateFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_StateFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_StateFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_StateFlag,
        qtscript_QStyle_StateFlag_valueOf, qtscript_QStyle_StateFlag_toString);
    qScriptRegisterMetaType<QStyle::StateFlag>(engine, qtscript_QStyle_StateFlag_toScriptValue,
        qtscript_QStyle_StateFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 28; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_StateFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_StateFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::State
//

static QScriptValue qtscript_QStyle_State_toScriptValue(QScriptEngine *engine, const QStyle::State &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyle_State_fromScriptValue(const QScriptValue &value, QStyle::State &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyle::State>())
        out = qvariant_cast<QStyle::State>(var);
    else if (var.userType() == qMetaTypeId<QStyle::StateFlag>())
        out = qvariant_cast<QStyle::StateFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyle_State(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::State result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyle::State>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyle::StateFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("State(): argument %0 is not of type StateFlag").arg(i));
            }
            result |= qvariant_cast<QStyle::StateFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyle_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::State value = qscriptvalue_cast<QStyle::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::State value = qscriptvalue_cast<QStyle::State>(context->thisObject());
    QString result;
    for (int i = 0; i < 28; ++i) {
        if ((value & qtscript_QStyle_StateFlag_values[i]) == qtscript_QStyle_StateFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyle_StateFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyle_State_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyle::State>() == otherObj.value<QStyle::State>())));
}

static QScriptValue qtscript_create_QStyle_State_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyle_State, qtscript_QStyle_State_valueOf,
        qtscript_QStyle_State_toString, qtscript_QStyle_State_equals);
    qScriptRegisterMetaType<QStyle::State>(engine, qtscript_QStyle_State_toScriptValue,
        qtscript_QStyle_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyle::ComplexControl
//

static const QStyle::ComplexControl qtscript_QStyle_ComplexControl_values[] = {
    QStyle::CC_CustomBase
    , QStyle::CC_SpinBox
    , QStyle::CC_ComboBox
    , QStyle::CC_ScrollBar
    , QStyle::CC_Slider
    , QStyle::CC_ToolButton
    , QStyle::CC_TitleBar
    , QStyle::CC_Q3ListView
    , QStyle::CC_Dial
    , QStyle::CC_GroupBox
    , QStyle::CC_MdiControls
};

static const char * const qtscript_QStyle_ComplexControl_keys[] = {
    "CC_CustomBase"
    , "CC_SpinBox"
    , "CC_ComboBox"
    , "CC_ScrollBar"
    , "CC_Slider"
    , "CC_ToolButton"
    , "CC_TitleBar"
    , "CC_Q3ListView"
    , "CC_Dial"
    , "CC_GroupBox"
    , "CC_MdiControls"
};

static QString qtscript_QStyle_ComplexControl_toStringHelper(QStyle::ComplexControl value)
{
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QStyle_ComplexControl_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_ComplexControl_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_ComplexControl_toScriptValue(QScriptEngine *engine, const QStyle::ComplexControl &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_ComplexControl_toStringHelper(value));
}

static void qtscript_QStyle_ComplexControl_fromScriptValue(const QScriptValue &value, QStyle::ComplexControl &out)
{
    out = qvariant_cast<QStyle::ComplexControl>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_ComplexControl(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QStyle_ComplexControl_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::ComplexControl>(arg));
    }
    return context->throwError(QString::fromLatin1("ComplexControl(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_ComplexControl_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::ComplexControl value = qscriptvalue_cast<QStyle::ComplexControl>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_ComplexControl_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::ComplexControl value = qscriptvalue_cast<QStyle::ComplexControl>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_ComplexControl_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_ComplexControl_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_ComplexControl,
        qtscript_QStyle_ComplexControl_valueOf, qtscript_QStyle_ComplexControl_toString);
    qScriptRegisterMetaType<QStyle::ComplexControl>(engine, qtscript_QStyle_ComplexControl_toScriptValue,
        qtscript_QStyle_ComplexControl_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_ComplexControl_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_ComplexControl_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::RequestSoftwareInputPanel
//

static const QStyle::RequestSoftwareInputPanel qtscript_QStyle_RequestSoftwareInputPanel_values[] = {
    QStyle::RSIP_OnMouseClickAndAlreadyFocused
    , QStyle::RSIP_OnMouseClick
};

static const char * const qtscript_QStyle_RequestSoftwareInputPanel_keys[] = {
    "RSIP_OnMouseClickAndAlreadyFocused"
    , "RSIP_OnMouseClick"
};

static QString qtscript_QStyle_RequestSoftwareInputPanel_toStringHelper(QStyle::RequestSoftwareInputPanel value)
{
    if ((value >= QStyle::RSIP_OnMouseClickAndAlreadyFocused) && (value <= QStyle::RSIP_OnMouseClick))
        return qtscript_QStyle_RequestSoftwareInputPanel_keys[static_cast<int>(value)-static_cast<int>(QStyle::RSIP_OnMouseClickAndAlreadyFocused)];
    return QString();
}

static QScriptValue qtscript_QStyle_RequestSoftwareInputPanel_toScriptValue(QScriptEngine *engine, const QStyle::RequestSoftwareInputPanel &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_RequestSoftwareInputPanel_toStringHelper(value));
}

static void qtscript_QStyle_RequestSoftwareInputPanel_fromScriptValue(const QScriptValue &value, QStyle::RequestSoftwareInputPanel &out)
{
    out = qvariant_cast<QStyle::RequestSoftwareInputPanel>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_RequestSoftwareInputPanel(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyle::RSIP_OnMouseClickAndAlreadyFocused) && (arg <= QStyle::RSIP_OnMouseClick))
        return qScriptValueFromValue(engine,  static_cast<QStyle::RequestSoftwareInputPanel>(arg));
    return context->throwError(QString::fromLatin1("RequestSoftwareInputPanel(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_RequestSoftwareInputPanel_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::RequestSoftwareInputPanel value = qscriptvalue_cast<QStyle::RequestSoftwareInputPanel>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_RequestSoftwareInputPanel_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::RequestSoftwareInputPanel value = qscriptvalue_cast<QStyle::RequestSoftwareInputPanel>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_RequestSoftwareInputPanel_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_RequestSoftwareInputPanel_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_RequestSoftwareInputPanel,
        qtscript_QStyle_RequestSoftwareInputPanel_valueOf, qtscript_QStyle_RequestSoftwareInputPanel_toString);
    qScriptRegisterMetaType<QStyle::RequestSoftwareInputPanel>(engine, qtscript_QStyle_RequestSoftwareInputPanel_toScriptValue,
        qtscript_QStyle_RequestSoftwareInputPanel_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_RequestSoftwareInputPanel_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_RequestSoftwareInputPanel_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle::SubElement
//

static const QStyle::SubElement qtscript_QStyle_SubElement_values[] = {
    QStyle::SE_CustomBase
    , QStyle::SE_PushButtonContents
    , QStyle::SE_PushButtonFocusRect
    , QStyle::SE_CheckBoxIndicator
    , QStyle::SE_CheckBoxContents
    , QStyle::SE_CheckBoxFocusRect
    , QStyle::SE_CheckBoxClickRect
    , QStyle::SE_RadioButtonIndicator
    , QStyle::SE_RadioButtonContents
    , QStyle::SE_RadioButtonFocusRect
    , QStyle::SE_RadioButtonClickRect
    , QStyle::SE_ComboBoxFocusRect
    , QStyle::SE_SliderFocusRect
    , QStyle::SE_Q3DockWindowHandleRect
    , QStyle::SE_ProgressBarGroove
    , QStyle::SE_ProgressBarContents
    , QStyle::SE_ProgressBarLabel
    , QStyle::SE_DialogButtonAccept
    , QStyle::SE_DialogButtonReject
    , QStyle::SE_DialogButtonApply
    , QStyle::SE_DialogButtonHelp
    , QStyle::SE_DialogButtonAll
    , QStyle::SE_DialogButtonAbort
    , QStyle::SE_DialogButtonIgnore
    , QStyle::SE_DialogButtonRetry
    , QStyle::SE_DialogButtonCustom
    , QStyle::SE_ToolBoxTabContents
    , QStyle::SE_HeaderLabel
    , QStyle::SE_HeaderArrow
    , QStyle::SE_TabWidgetTabBar
    , QStyle::SE_TabWidgetTabPane
    , QStyle::SE_TabWidgetTabContents
    , QStyle::SE_TabWidgetLeftCorner
    , QStyle::SE_TabWidgetRightCorner
    , QStyle::SE_ViewItemCheckIndicator
    , QStyle::SE_TabBarTearIndicator
    , QStyle::SE_TreeViewDisclosureItem
    , QStyle::SE_LineEditContents
    , QStyle::SE_FrameContents
    , QStyle::SE_DockWidgetCloseButton
    , QStyle::SE_DockWidgetFloatButton
    , QStyle::SE_DockWidgetTitleBarText
    , QStyle::SE_DockWidgetIcon
    , QStyle::SE_CheckBoxLayoutItem
    , QStyle::SE_ComboBoxLayoutItem
    , QStyle::SE_DateTimeEditLayoutItem
    , QStyle::SE_DialogButtonBoxLayoutItem
    , QStyle::SE_LabelLayoutItem
    , QStyle::SE_ProgressBarLayoutItem
    , QStyle::SE_PushButtonLayoutItem
    , QStyle::SE_RadioButtonLayoutItem
    , QStyle::SE_SliderLayoutItem
    , QStyle::SE_SpinBoxLayoutItem
    , QStyle::SE_ToolButtonLayoutItem
    , QStyle::SE_FrameLayoutItem
    , QStyle::SE_GroupBoxLayoutItem
    , QStyle::SE_TabWidgetLayoutItem
    , QStyle::SE_ItemViewItemDecoration
    , QStyle::SE_ItemViewItemText
    , QStyle::SE_ItemViewItemFocusRect
    , QStyle::SE_TabBarTabLeftButton
    , QStyle::SE_TabBarTabRightButton
    , QStyle::SE_TabBarTabText
    , QStyle::SE_ShapedFrameContents
    , QStyle::SE_ToolBarHandle
};

static const char * const qtscript_QStyle_SubElement_keys[] = {
    "SE_CustomBase"
    , "SE_PushButtonContents"
    , "SE_PushButtonFocusRect"
    , "SE_CheckBoxIndicator"
    , "SE_CheckBoxContents"
    , "SE_CheckBoxFocusRect"
    , "SE_CheckBoxClickRect"
    , "SE_RadioButtonIndicator"
    , "SE_RadioButtonContents"
    , "SE_RadioButtonFocusRect"
    , "SE_RadioButtonClickRect"
    , "SE_ComboBoxFocusRect"
    , "SE_SliderFocusRect"
    , "SE_Q3DockWindowHandleRect"
    , "SE_ProgressBarGroove"
    , "SE_ProgressBarContents"
    , "SE_ProgressBarLabel"
    , "SE_DialogButtonAccept"
    , "SE_DialogButtonReject"
    , "SE_DialogButtonApply"
    , "SE_DialogButtonHelp"
    , "SE_DialogButtonAll"
    , "SE_DialogButtonAbort"
    , "SE_DialogButtonIgnore"
    , "SE_DialogButtonRetry"
    , "SE_DialogButtonCustom"
    , "SE_ToolBoxTabContents"
    , "SE_HeaderLabel"
    , "SE_HeaderArrow"
    , "SE_TabWidgetTabBar"
    , "SE_TabWidgetTabPane"
    , "SE_TabWidgetTabContents"
    , "SE_TabWidgetLeftCorner"
    , "SE_TabWidgetRightCorner"
    , "SE_ViewItemCheckIndicator"
    , "SE_TabBarTearIndicator"
    , "SE_TreeViewDisclosureItem"
    , "SE_LineEditContents"
    , "SE_FrameContents"
    , "SE_DockWidgetCloseButton"
    , "SE_DockWidgetFloatButton"
    , "SE_DockWidgetTitleBarText"
    , "SE_DockWidgetIcon"
    , "SE_CheckBoxLayoutItem"
    , "SE_ComboBoxLayoutItem"
    , "SE_DateTimeEditLayoutItem"
    , "SE_DialogButtonBoxLayoutItem"
    , "SE_LabelLayoutItem"
    , "SE_ProgressBarLayoutItem"
    , "SE_PushButtonLayoutItem"
    , "SE_RadioButtonLayoutItem"
    , "SE_SliderLayoutItem"
    , "SE_SpinBoxLayoutItem"
    , "SE_ToolButtonLayoutItem"
    , "SE_FrameLayoutItem"
    , "SE_GroupBoxLayoutItem"
    , "SE_TabWidgetLayoutItem"
    , "SE_ItemViewItemDecoration"
    , "SE_ItemViewItemText"
    , "SE_ItemViewItemFocusRect"
    , "SE_TabBarTabLeftButton"
    , "SE_TabBarTabRightButton"
    , "SE_TabBarTabText"
    , "SE_ShapedFrameContents"
    , "SE_ToolBarHandle"
};

static QString qtscript_QStyle_SubElement_toStringHelper(QStyle::SubElement value)
{
    for (int i = 0; i < 65; ++i) {
        if (qtscript_QStyle_SubElement_values[i] == value)
            return QString::fromLatin1(qtscript_QStyle_SubElement_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyle_SubElement_toScriptValue(QScriptEngine *engine, const QStyle::SubElement &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyle"));
    return clazz.property(qtscript_QStyle_SubElement_toStringHelper(value));
}

static void qtscript_QStyle_SubElement_fromScriptValue(const QScriptValue &value, QStyle::SubElement &out)
{
    out = qvariant_cast<QStyle::SubElement>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyle_SubElement(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 65; ++i) {
        if (qtscript_QStyle_SubElement_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyle::SubElement>(arg));
    }
    return context->throwError(QString::fromLatin1("SubElement(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyle_SubElement_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::SubElement value = qscriptvalue_cast<QStyle::SubElement>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyle_SubElement_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyle::SubElement value = qscriptvalue_cast<QStyle::SubElement>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyle_SubElement_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyle_SubElement_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyle_SubElement,
        qtscript_QStyle_SubElement_valueOf, qtscript_QStyle_SubElement_toString);
    qScriptRegisterMetaType<QStyle::SubElement>(engine, qtscript_QStyle_SubElement_toScriptValue,
        qtscript_QStyle_SubElement_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 65; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyle_SubElement_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyle_SubElement_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyle
//

static QScriptValue qtscript_QStyle_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 21;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStyle* _q_self = qscriptvalue_cast<QStyle*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyle.%0(): this object is not a QStyle")
            .arg(qtscript_QStyle_function_names[_id+7]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QFlags<QSizePolicy::ControlType> _q_arg0 = qscriptvalue_cast<QFlags<QSizePolicy::ControlType> >(context->argument(0));
        QFlags<QSizePolicy::ControlType> _q_arg1 = qscriptvalue_cast<QFlags<QSizePolicy::ControlType> >(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        int _q_result = _q_self->combinedLayoutSpacing(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QFlags<QSizePolicy::ControlType> _q_arg0 = qscriptvalue_cast<QFlags<QSizePolicy::ControlType> >(context->argument(0));
        QFlags<QSizePolicy::ControlType> _q_arg1 = qscriptvalue_cast<QFlags<QSizePolicy::ControlType> >(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        QStyleOption* _q_arg3 = qscriptvalue_cast<QStyleOption*>(context->argument(3));
        int _q_result = _q_self->combinedLayoutSpacing(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QFlags<QSizePolicy::ControlType> _q_arg0 = qscriptvalue_cast<QFlags<QSizePolicy::ControlType> >(context->argument(0));
        QFlags<QSizePolicy::ControlType> _q_arg1 = qscriptvalue_cast<QFlags<QSizePolicy::ControlType> >(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        QStyleOption* _q_arg3 = qscriptvalue_cast<QStyleOption*>(context->argument(3));
        QWidget* _q_arg4 = qscriptvalue_cast<QWidget*>(context->argument(4));
        int _q_result = _q_self->combinedLayoutSpacing(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QStyle::ComplexControl _q_arg0 = qscriptvalue_cast<QStyle::ComplexControl>(context->argument(0));
        QStyleOptionComplex* _q_arg1 = qscriptvalue_cast<QStyleOptionComplex*>(context->argument(1));
        QPainter* _q_arg2 = qscriptvalue_cast<QPainter*>(context->argument(2));
        _q_self->drawComplexControl(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QStyle::ComplexControl _q_arg0 = qscriptvalue_cast<QStyle::ComplexControl>(context->argument(0));
        QStyleOptionComplex* _q_arg1 = qscriptvalue_cast<QStyleOptionComplex*>(context->argument(1));
        QPainter* _q_arg2 = qscriptvalue_cast<QPainter*>(context->argument(2));
        QWidget* _q_arg3 = qscriptvalue_cast<QWidget*>(context->argument(3));
        _q_self->drawComplexControl(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QStyle::ControlElement _q_arg0 = qscriptvalue_cast<QStyle::ControlElement>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QPainter* _q_arg2 = qscriptvalue_cast<QPainter*>(context->argument(2));
        _q_self->drawControl(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QStyle::ControlElement _q_arg0 = qscriptvalue_cast<QStyle::ControlElement>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QPainter* _q_arg2 = qscriptvalue_cast<QPainter*>(context->argument(2));
        QWidget* _q_arg3 = qscriptvalue_cast<QWidget*>(context->argument(3));
        _q_self->drawControl(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QPixmap _q_arg3 = qscriptvalue_cast<QPixmap>(context->argument(3));
        _q_self->drawItemPixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 6) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QPalette _q_arg3 = qscriptvalue_cast<QPalette>(context->argument(3));
        bool _q_arg4 = context->argument(4).toBoolean();
        QString _q_arg5 = context->argument(5).toString();
        _q_self->drawItemText(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QPalette _q_arg3 = qscriptvalue_cast<QPalette>(context->argument(3));
        bool _q_arg4 = context->argument(4).toBoolean();
        QString _q_arg5 = context->argument(5).toString();
        QPalette::ColorRole _q_arg6 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(6));
        _q_self->drawItemText(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        QStyle::PrimitiveElement _q_arg0 = qscriptvalue_cast<QStyle::PrimitiveElement>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QPainter* _q_arg2 = qscriptvalue_cast<QPainter*>(context->argument(2));
        _q_self->drawPrimitive(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QStyle::PrimitiveElement _q_arg0 = qscriptvalue_cast<QStyle::PrimitiveElement>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QPainter* _q_arg2 = qscriptvalue_cast<QPainter*>(context->argument(2));
        QWidget* _q_arg3 = qscriptvalue_cast<QWidget*>(context->argument(3));
        _q_self->drawPrimitive(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        QIcon::Mode _q_arg0 = qscriptvalue_cast<QIcon::Mode>(context->argument(0));
        QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
        QStyleOption* _q_arg2 = qscriptvalue_cast<QStyleOption*>(context->argument(2));
        QPixmap _q_result = _q_self->generatedIconPixmap(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        QStyle::ComplexControl _q_arg0 = qscriptvalue_cast<QStyle::ComplexControl>(context->argument(0));
        QStyleOptionComplex* _q_arg1 = qscriptvalue_cast<QStyleOptionComplex*>(context->argument(1));
        QPoint _q_arg2 = qscriptvalue_cast<QPoint>(context->argument(2));
        QStyle::SubControl _q_result = _q_self->hitTestComplexControl(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QStyle::ComplexControl _q_arg0 = qscriptvalue_cast<QStyle::ComplexControl>(context->argument(0));
        QStyleOptionComplex* _q_arg1 = qscriptvalue_cast<QStyleOptionComplex*>(context->argument(1));
        QPoint _q_arg2 = qscriptvalue_cast<QPoint>(context->argument(2));
        QWidget* _q_arg3 = qscriptvalue_cast<QWidget*>(context->argument(3));
        QStyle::SubControl _q_result = _q_self->hitTestComplexControl(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 3) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QPixmap _q_arg2 = qscriptvalue_cast<QPixmap>(context->argument(2));
        QRect _q_result = _q_self->itemPixmapRect(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 3) {
        QSizePolicy::ControlType _q_arg0 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(0));
        QSizePolicy::ControlType _q_arg1 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        int _q_result = _q_self->layoutSpacing(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QSizePolicy::ControlType _q_arg0 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(0));
        QSizePolicy::ControlType _q_arg1 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        QStyleOption* _q_arg3 = qscriptvalue_cast<QStyleOption*>(context->argument(3));
        int _q_result = _q_self->layoutSpacing(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QSizePolicy::ControlType _q_arg0 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(0));
        QSizePolicy::ControlType _q_arg1 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        QStyleOption* _q_arg3 = qscriptvalue_cast<QStyleOption*>(context->argument(3));
        QWidget* _q_arg4 = qscriptvalue_cast<QWidget*>(context->argument(4));
        int _q_result = _q_self->layoutSpacing(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QStyle::PixelMetric _q_arg0 = qscriptvalue_cast<QStyle::PixelMetric>(context->argument(0));
        int _q_result = _q_self->pixelMetric(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QStyle::PixelMetric _q_arg0 = qscriptvalue_cast<QStyle::PixelMetric>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        int _q_result = _q_self->pixelMetric(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QStyle::PixelMetric _q_arg0 = qscriptvalue_cast<QStyle::PixelMetric>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        int _q_result = _q_self->pixelMetric(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QApplication*>(context->argument(0))) {
            QApplication* _q_arg0 = qscriptvalue_cast<QApplication*>(context->argument(0));
            _q_self->polish(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPalette>() == context->argument(0).toVariant().userType())) {
            QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));
            _q_self->polish(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            _q_self->polish(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QStyle* _q_result = const_cast<QStyle*>(_q_self->proxy());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 3) {
        QStyle::ContentsType _q_arg0 = qscriptvalue_cast<QStyle::ContentsType>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QSize _q_arg2 = qscriptvalue_cast<QSize>(context->argument(2));
        QSize _q_result = _q_self->sizeFromContents(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QStyle::ContentsType _q_arg0 = qscriptvalue_cast<QStyle::ContentsType>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QSize _q_arg2 = qscriptvalue_cast<QSize>(context->argument(2));
        QWidget* _q_arg3 = qscriptvalue_cast<QWidget*>(context->argument(3));
        QSize _q_result = _q_self->sizeFromContents(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QStyle::StandardPixmap _q_arg0 = qscriptvalue_cast<QStyle::StandardPixmap>(context->argument(0));
        QIcon _q_result = _q_self->standardIcon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QStyle::StandardPixmap _q_arg0 = qscriptvalue_cast<QStyle::StandardPixmap>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QIcon _q_result = _q_self->standardIcon(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QStyle::StandardPixmap _q_arg0 = qscriptvalue_cast<QStyle::StandardPixmap>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QIcon _q_result = _q_self->standardIcon(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QPalette _q_result = _q_self->standardPalette();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QStyle::StandardPixmap _q_arg0 = qscriptvalue_cast<QStyle::StandardPixmap>(context->argument(0));
        QPixmap _q_result = _q_self->standardPixmap(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QStyle::StandardPixmap _q_arg0 = qscriptvalue_cast<QStyle::StandardPixmap>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QPixmap _q_result = _q_self->standardPixmap(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QStyle::StandardPixmap _q_arg0 = qscriptvalue_cast<QStyle::StandardPixmap>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QPixmap _q_result = _q_self->standardPixmap(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QStyle::StyleHint _q_arg0 = qscriptvalue_cast<QStyle::StyleHint>(context->argument(0));
        int _q_result = _q_self->styleHint(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QStyle::StyleHint _q_arg0 = qscriptvalue_cast<QStyle::StyleHint>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        int _q_result = _q_self->styleHint(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QStyle::StyleHint _q_arg0 = qscriptvalue_cast<QStyle::StyleHint>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        int _q_result = _q_self->styleHint(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QStyle::StyleHint _q_arg0 = qscriptvalue_cast<QStyle::StyleHint>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QStyleHintReturn* _q_arg3 = qscriptvalue_cast<QStyleHintReturn*>(context->argument(3));
        int _q_result = _q_self->styleHint(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 3) {
        QStyle::ComplexControl _q_arg0 = qscriptvalue_cast<QStyle::ComplexControl>(context->argument(0));
        QStyleOptionComplex* _q_arg1 = qscriptvalue_cast<QStyleOptionComplex*>(context->argument(1));
        QStyle::SubControl _q_arg2 = qscriptvalue_cast<QStyle::SubControl>(context->argument(2));
        QRect _q_result = _q_self->subControlRect(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QStyle::ComplexControl _q_arg0 = qscriptvalue_cast<QStyle::ComplexControl>(context->argument(0));
        QStyleOptionComplex* _q_arg1 = qscriptvalue_cast<QStyleOptionComplex*>(context->argument(1));
        QStyle::SubControl _q_arg2 = qscriptvalue_cast<QStyle::SubControl>(context->argument(2));
        QWidget* _q_arg3 = qscriptvalue_cast<QWidget*>(context->argument(3));
        QRect _q_result = _q_self->subControlRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        QStyle::SubElement _q_arg0 = qscriptvalue_cast<QStyle::SubElement>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QRect _q_result = _q_self->subElementRect(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QStyle::SubElement _q_arg0 = qscriptvalue_cast<QStyle::SubElement>(context->argument(0));
        QStyleOption* _q_arg1 = qscriptvalue_cast<QStyleOption*>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QRect _q_result = _q_self->subElementRect(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QApplication*>(context->argument(0))) {
            QApplication* _q_arg0 = qscriptvalue_cast<QApplication*>(context->argument(0));
            _q_self->unpolish(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            _q_self->unpolish(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("QStyle");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyle_throw_ambiguity_error_helper(context,
        qtscript_QStyle_function_names[_id+7],
        qtscript_QStyle_function_signatures[_id+7]);
}

static QScriptValue qtscript_QStyle_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyle(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyle* _q_cpp_result = new QtScriptShell_QStyle();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStyle*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 4) {
        Qt::LayoutDirection _q_arg0 = qscriptvalue_cast<Qt::LayoutDirection>(context->argument(0));
        QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
        QSize _q_arg2 = qscriptvalue_cast<QSize>(context->argument(2));
        QRect _q_arg3 = qscriptvalue_cast<QRect>(context->argument(3));
        QRect _q_result = QStyle::alignedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_result = QStyle::sliderPositionFromValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_arg4 = context->argument(4).toBoolean();
        int _q_result = QStyle::sliderPositionFromValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_result = QStyle::sliderValueFromPosition(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_arg4 = context->argument(4).toBoolean();
        int _q_result = QStyle::sliderValueFromPosition(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        Qt::LayoutDirection _q_arg0 = qscriptvalue_cast<Qt::LayoutDirection>(context->argument(0));
        QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
        QFlags<Qt::AlignmentFlag> _q_result = QStyle::visualAlignment(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        Qt::LayoutDirection _q_arg0 = qscriptvalue_cast<Qt::LayoutDirection>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        QPoint _q_arg2 = qscriptvalue_cast<QPoint>(context->argument(2));
        QPoint _q_result = QStyle::visualPos(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        Qt::LayoutDirection _q_arg0 = qscriptvalue_cast<Qt::LayoutDirection>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        QRect _q_result = QStyle::visualRect(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyle_throw_ambiguity_error_helper(context,
        qtscript_QStyle_function_names[_id],
        qtscript_QStyle_function_signatures[_id]);
}

static QScriptValue qtscript_QStyle_toScriptValue(QScriptEngine *engine, QStyle* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStyle_fromScriptValue(const QScriptValue &value, QStyle* &out)
{
    out = qobject_cast<QStyle*>(value.toQObject());
}

QScriptValue qtscript_create_QStyle_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyle*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyle*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStyle_prototype_call, qtscript_QStyle_function_lengths[i+7]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStyle_function_names[i+7]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStyle*>(engine, qtscript_QStyle_toScriptValue, 
        qtscript_QStyle_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyle_static_call, proto, qtscript_QStyle_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStyle_static_call,
            qtscript_QStyle_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QStyle_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("PixelMetric"),
        qtscript_create_QStyle_PixelMetric_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SubControl"),
        qtscript_create_QStyle_SubControl_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SubControls"),
        qtscript_create_QStyle_SubControls_class(engine));
    ctor.setProperty(QString::fromLatin1("StandardPixmap"),
        qtscript_create_QStyle_StandardPixmap_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleHint"),
        qtscript_create_QStyle_StyleHint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PrimitiveElement"),
        qtscript_create_QStyle_PrimitiveElement_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ControlElement"),
        qtscript_create_QStyle_ControlElement_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ContentsType"),
        qtscript_create_QStyle_ContentsType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StateFlag"),
        qtscript_create_QStyle_StateFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QStyle_State_class(engine));
    ctor.setProperty(QString::fromLatin1("ComplexControl"),
        qtscript_create_QStyle_ComplexControl_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RequestSoftwareInputPanel"),
        qtscript_create_QStyle_RequestSoftwareInputPanel_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SubElement"),
        qtscript_create_QStyle_SubElement_class(engine, ctor));
    return ctor;
}
