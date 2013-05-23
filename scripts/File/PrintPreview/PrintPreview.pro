NAME = $${TARGET}
TSDIR = ts
include(../../translations.pri)
SOURCES = $${TARGET}.js $${TARGET}Init.js
FORMS = $${TARGET}.ui
OTHER_FILES = \
    doc/$${TARGET}_desc_en.html
