#ifndef QTSCRIPTSHELL_ABSTRACTVIDEOWIDGET_H
#define QTSCRIPTSHELL_ABSTRACTVIDEOWIDGET_H

#include <videowidgetinterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractVideoWidget : public Phonon::VideoWidgetInterface
{
public:
    QtScriptShell_AbstractVideoWidget();
    ~QtScriptShell_AbstractVideoWidget();

    Phonon::VideoWidget::AspectRatio  aspectRatio() const;
    qreal  brightness() const;
    qreal  contrast() const;
    qreal  hue() const;
    qreal  saturation() const;
    Phonon::VideoWidget::ScaleMode  scaleMode() const;
    void setAspectRatio(Phonon::VideoWidget::AspectRatio  arg__1);
    void setBrightness(qreal  arg__1);
    void setContrast(qreal  arg__1);
    void setHue(qreal  arg__1);
    void setSaturation(qreal  arg__1);
    void setScaleMode(Phonon::VideoWidget::ScaleMode  arg__1);
    QWidget*  widget();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTVIDEOWIDGET_H
