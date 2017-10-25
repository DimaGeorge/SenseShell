#made by dima

TEMPLATE = app
TARGET = 
DEPENDPATH += . Business Data GUI Status utils
INCLUDEPATH += . Business Status Data GUI
CONFIG = qt thread x11


# Input
HEADERS += Business/ssBusinessManager.h \
           Business/ssInterpreter.h \
           Data/ssDataManager.h \
           GUI/ssGUIManager.h \
           Status/ssBuffer.h \
           Status/ssInputBuffer.h \
           Status/ssOutputBuffer.h \
           Status/ssStatusTable.h \
           Status/ssSugestionBuffer.h \
           utils/utils.h

SOURCES += Business/ssBusinessManager.cpp \
           Business/ssInterpreter.cpp \
           Data/ssDataManager.cpp \
           GUI/ssGUIManager.cpp \
           Status/main.cpp \
           Status/ssBuffer.cpp \
           Status/ssInputBuffer.cpp \
           Status/ssOutputBuffer.cpp \
           Status/ssStatusTable.cpp \
           Status/ssSugestionBuffer.cpp
