QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backend.cpp \
    choose.cpp \
    file.cpp \
    highlighter.cpp \
    main.cpp \
    pluginconfigure.cpp \
    project.cpp \
    projectitem.cpp \
    projectmodel.cpp \
    textedit.cpp \
    treenode.cpp \
    ui_plugin.cpp \
    uimain.cpp \
    util.cpp

HEADERS += \
    backend.h \
    choose.h \
    file.h \
    highlighter.h \
    pluginconfigure.h \
    project.h \
    projectitem.h \
    projectmodel.h \
    textedit.h \
    treenode.h \
    ui_plugin.h \
    uimain.h \
    util.h

FORMS += \
    choose.ui \
    main.ui \
    ui_plugin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    file.qrc \
    icon.qrc
