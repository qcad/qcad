NAME = $${TARGET} 
TSDIR = ts
include(../../translations.pri)
SOURCES = $${TARGET}.js

exists(PreferencesPage.ui){
	FORMS = PreferencesPage.ui
}
