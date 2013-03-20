NAME = $${TARGET} 
TSDIR = ts
include(../../translations.pri)
SOURCES = $${TARGET}.js $${TARGET}Init.js

exists($${TARGET}.ui){
	FORMS = $${TARGET}.ui
}
 
