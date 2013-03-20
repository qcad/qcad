NAME = $${TARGET} 
SOURCES = $${TARGET}.js $${TARGET}Init.js
TSDIR = ts
include(../../translations.pri)
FORMS = BitmapExportDialog.ui
OTHER_FILES = \
    doc/$${TARGET}_desc_en.html \
    doc/$${TARGET}_proc_en.html
