NAME = $${TARGET}
TSDIR = ts
include(../../translations.pri)
SOURCES = $${TARGET}.js $${TARGET}Init.js \
    TextDialog/TextDialog.js \
    TextDialog/CharacterMapDialog.js
FORMS = $${TARGET}.ui \
    TextDialog/CharacterMapDialog.ui \
    TextDialog/TextDialog.ui
