QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form_tree.cpp \
    huffmanCompressor.cpp \
    indentation.cpp \
    main.cpp \
    mainwindow.cpp \
    minify.cpp \
    parsing_xml.cpp \
    xml_tree.cpp \
    xml_validator.cpp \
    xmljson.cpp

HEADERS += \
    form_tree.h \
    huffmanCompressorHeader.h \
    indentaion.h \
    mainwindow.h \
    minify.h \
    parsing_xml.h \
    xml_tree.h \
    xml_validator.h \
    xmljson.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourcces.qrc
