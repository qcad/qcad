NAME = $${TARGET} 
TSDIR = ts
include(../../translations.pri)
SOURCES = $${TARGET}.js $${TARGET}Init.js
FORMS = $${TARGET}Dialog.ui PreferencesPage.ui
OTHER_FILES = \
    doc/Explode_desc_en.html \
    doc/Explode_proc_en.html
