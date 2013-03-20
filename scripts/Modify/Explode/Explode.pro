NAME = $${TARGET} 
TSDIR = ts
include(../../translations.pri)
SOURCES = $${TARGET}.js $${TARGET}Init.js
FORMS = ExplodeDialog.ui PreferencesPage.ui
OTHER_FILES = \
    doc/Explode_desc_en.html \
    doc/Explode_proc_en.html
