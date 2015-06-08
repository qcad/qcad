#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_EffectParameter_class(QScriptEngine *engine);
QScriptValue qtscript_create_AudioOutputDevice_class(QScriptEngine *engine);
QScriptValue qtscript_create_MediaNode_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractStream_class(QScriptEngine *engine);
QScriptValue qtscript_create_AudioCaptureDevice_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractBackend_class(QScriptEngine *engine);
QScriptValue qtscript_create_Phonon_class(QScriptEngine *engine);
QScriptValue qtscript_create_PlatformPlugin_class(QScriptEngine *engine);
QScriptValue qtscript_create_SubtitleDescription_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractMediaObject_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractVolumeFader_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractVideoWidget_class(QScriptEngine *engine);
QScriptValue qtscript_create_BackendCapabilities_class(QScriptEngine *engine);
QScriptValue qtscript_create_EffectDescription_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractEffect_class(QScriptEngine *engine);
QScriptValue qtscript_create_MediaSource_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractAddon_class(QScriptEngine *engine);
QScriptValue qtscript_create_AudioChannelDescription_class(QScriptEngine *engine);
QScriptValue qtscript_create_Path_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractVideoOutput_class(QScriptEngine *engine);
QScriptValue qtscript_create_MediaObject_class(QScriptEngine *engine);
QScriptValue qtscript_create_MediaController_class(QScriptEngine *engine);
QScriptValue qtscript_create_Effect_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractAudioOutput_class(QScriptEngine *engine);
QScriptValue qtscript_create_AbstractMediaStream_class(QScriptEngine *engine);
QScriptValue qtscript_create_SeekSlider_class(QScriptEngine *engine);
QScriptValue qtscript_create_AudioOutput_class(QScriptEngine *engine);
QScriptValue qtscript_create_EffectWidget_class(QScriptEngine *engine);
QScriptValue qtscript_create_VolumeFaderEffect_class(QScriptEngine *engine);
QScriptValue qtscript_create_VideoPlayer_class(QScriptEngine *engine);
QScriptValue qtscript_create_VolumeSlider_class(QScriptEngine *engine);
QScriptValue qtscript_create_VideoWidget_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_phonon_class_names[] = {
    "EffectParameter"
    , "AudioOutputDevice"
    , "MediaNode"
    , "AbstractStream"
    , "AudioCaptureDevice"
    , "AbstractBackend"
    , "Phonon"
    , "PlatformPlugin"
    , "SubtitleDescription"
    , "AbstractMediaObject"
    , "AbstractVolumeFader"
    , "AbstractVideoWidget"
    , "BackendCapabilities"
    , "EffectDescription"
    , "AbstractEffect"
    , "MediaSource"
    , "AbstractAddon"
    , "AudioChannelDescription"
    , "Path"
    , "AbstractVideoOutput"
    , "MediaObject"
    , "MediaController"
    , "Effect"
    , "AbstractAudioOutput"
    , "AbstractMediaStream"
    , "SeekSlider"
    , "AudioOutput"
    , "EffectWidget"
    , "VolumeFaderEffect"
    , "VideoPlayer"
    , "VolumeSlider"
    , "VideoWidget"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_phonon_class_functions[] = {
    qtscript_create_EffectParameter_class
    , qtscript_create_AudioOutputDevice_class
    , qtscript_create_MediaNode_class
    , qtscript_create_AbstractStream_class
    , qtscript_create_AudioCaptureDevice_class
    , qtscript_create_AbstractBackend_class
    , qtscript_create_Phonon_class
    , qtscript_create_PlatformPlugin_class
    , qtscript_create_SubtitleDescription_class
    , qtscript_create_AbstractMediaObject_class
    , qtscript_create_AbstractVolumeFader_class
    , qtscript_create_AbstractVideoWidget_class
    , qtscript_create_BackendCapabilities_class
    , qtscript_create_EffectDescription_class
    , qtscript_create_AbstractEffect_class
    , qtscript_create_MediaSource_class
    , qtscript_create_AbstractAddon_class
    , qtscript_create_AudioChannelDescription_class
    , qtscript_create_Path_class
    , qtscript_create_AbstractVideoOutput_class
    , qtscript_create_MediaObject_class
    , qtscript_create_MediaController_class
    , qtscript_create_Effect_class
    , qtscript_create_AbstractAudioOutput_class
    , qtscript_create_AbstractMediaStream_class
    , qtscript_create_SeekSlider_class
    , qtscript_create_AudioOutput_class
    , qtscript_create_EffectWidget_class
    , qtscript_create_VolumeFaderEffect_class
    , qtscript_create_VideoPlayer_class
    , qtscript_create_VolumeSlider_class
    , qtscript_create_VideoWidget_class
};

void qtscript_initialize_com_trolltech_qt_phonon_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 32; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_phonon_class_names[i],
            qtscript_com_trolltech_qt_phonon_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
