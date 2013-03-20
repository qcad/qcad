NAME = $${TARGET} 
TSDIR = ts
include(../../../translations.pri)
SOURCES = $${TARGET}.js $${TARGET}Init.js

exists(PreferencesPage.ui){
	FORMS = PreferencesPage.ui
}
