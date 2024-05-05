QT += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../View/main.cpp \
    ../View/view.cpp \
    ../Model/parce_obj.cc \
    ../Model/model.cc \
    ../Model/lexem.cc \
    ../Controller/controller.cc \
    ../Model/affine_transformations.cc


HEADERS += \
    view.h \
    ../Model/parce_obj.h \
    ../View/view.h \
    ../Model/model.h \
    ../Controller/controller.h \
    ../Model/data_3d_model.h \
    ../Model/affine_transformations.h


FORMS += \
    mainwindow.ui

linux: {
    INCLUDEPATH += /usr/include/GL
    LIBS += -lGL -lGLU
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
