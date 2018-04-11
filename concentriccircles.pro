QT += widgets
CONFIG += c++11
HEADERS       = circlewidget.h \
                window.h \
    physycobject.h \
    basictypes.h \
    datareader.h
SOURCES       = circlewidget.cpp \
                main.cpp \
                window.cpp \
    physycobject.cpp \
    datareader.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/concentriccircles
INSTALLS += target

DISTFILES += \
    objectData.txt
