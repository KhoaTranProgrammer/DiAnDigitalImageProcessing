QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    ../../source/DADIP_BMP.c \
    ../../source/DADIP_Convert.c \
    ../../source/DADIP_FileIO.c \
    ../../source/DADIP_Filter.c \
    ../../source/DADIP_Geometry.c \
    ../../source/DADIP_Histogram.c \
    ../../source/DADIP_ImageIO.c \
    ../../source/DADIP_Math.c \
    ../../source/DADIP_Overlay.c \
    ../../source/DADIP_Rotate.c \
    ../../source/DADIP_Utility.c \
    ../../source/DADIP_Warping.c

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../include/DADIP_BMP.h \
    ../../include/DADIP_Convert.h \
    ../../include/DADIP_FileIO.h \
    ../../include/DADIP_Filter.h \
    ../../include/DADIP_Geometry.h \
    ../../include/DADIP_Histogram.h \
    ../../include/DADIP_ImageIO.h \
    ../../include/DADIP_Math.h \
    ../../include/DADIP_Overlay.h \
    ../../include/DADIP_Rotate.h \
    ../../include/DADIP_Type.h \
    ../../include/DADIP_Utility.h \
    ../../include/DADIP_Warping.h

INCLUDEPATH += $$PWD/../../include/
