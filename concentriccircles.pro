QT += widgets
CONFIG += c++11
HEADERS       = \
                window.h \
    physycobject.h \
    basictypes.h \
    datareader.h \
    PhPhysycalView.h
SOURCES       = \
                main.cpp \
                window.cpp \
    physycobject.cpp \
    datareader.cpp \
    PhPhysycalView.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/concentriccircles
INSTALLS += target

DISTFILES += \
    objectData.txt
