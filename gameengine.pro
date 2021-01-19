QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    gamecomponent.cpp \
    gameobject.cpp \
    mesh.cpp \
    meshrenderer.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \

HEADERS += \
    BasicIO.h \
    gamecomponent.h \
    gameobject.h \
    mainwidget.h \
    mesh.h \
    meshrenderer.h \
    transform.h

RESOURCES += \
    file.qrc \
    shaders.qrc \
    textures.qrc
# install
target.path = $$[YOUR_PATH]
INSTALLS += target

DISTFILES +=
