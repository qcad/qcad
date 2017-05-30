NAME = $${TARGET}
TSDIR = ts
include(../../translations.pri)
SOURCES = $${TARGET}.js $${TARGET}Init.js \
    TextAlongDialog/TextDialog.js \
    TextAlongDialog/CharacterMapDialog.js
FORMS = $${TARGET}.ui \
    TextAlongDialog/CharacterMapDialog.ui \
    TextAlongDialog/TextDialog.ui
