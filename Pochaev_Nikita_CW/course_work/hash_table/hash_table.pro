QT += core gui widgets
TEMPLATE = app
CONFIG += c++17 resources_big
SOURCES = mainwindow.cpp \
    TableHandler.cpp \
    drawingwindow.cpp \
    functionsForDrawing.cpp \
    main.cpp \
    setupUI.cpp
HEADERS += \
    HashTable.h \
    TableHandler.h \
    allheaders.h \
    drawingwindow.h \
    mainwindow.h
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
TARGET = hash_table
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a

RESOURCES +=

FORMS +=
