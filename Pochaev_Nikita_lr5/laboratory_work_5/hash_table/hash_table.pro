QT += core gui widgets
TEMPLATE = app
CONFIG += c++17
SOURCES = mainwindow.cpp \
    main.cpp \
    setupUI.cpp \
    test.cpp
HEADERS += \
    HashTable.h \
    allheaders.h \
    customvector.h \
    mainwindow.h \
    test.h \
    ui_mainwindow.h
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
TARGET = hash_table
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a

RESOURCES +=

FORMS += \
    mainwindow.ui
