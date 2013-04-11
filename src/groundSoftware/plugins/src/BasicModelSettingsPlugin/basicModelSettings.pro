TEMPLATE = lib
LANGUAGE = C++

CONFIG  += qt warn_on release plugin
QMAKE_CXXFLAGS += -Wno-deprecated -fPIC
QT += xml network

DEFINES += VERSION=QString\\\(\\\"1.0-0\\\"\\\)

HEADERS += ../../../pluginInterfaces.h \
           ../../../gfxDisplay.h \
           ../../../gfxObject.h \
           ../../../gfxRhino3D.h \
           ../../../gfxOSM.h \
           ../../../gfxOSMnode.h \
           ../../../gfxOSMway.h

HEADERS += basicModelSettings.h

SOURCES += basicModelSettings.cpp \
           ../../../gfxDisplay.cpp \
           ../../../gfxObject.cpp \
           ../../../gfxRhino3D.cpp \
           ../../../gfxOSM.cpp \
           ../../../gfxOSMnode.cpp \
           ../../../gfxOSMway.cpp

ARCH  = $$system("uname -m")
OPSYS = $$system("uname")
DESTDIR = ../../

# VTK
INCLUDEPATH += /usr/include/vtk-5.8
LIBS += -L/usr/lib/vtk-5.8 -lQVTK -lvtkCommon -lvtksys -lvtkRendering
LIBS += -lvtkGraphics -lvtkFiltering
#LIBS += ../../../openNURBS-5/libopenNURBS.a
LIBS +=   ../../../openNURBS-5/libopenNurbs-5.so

UI_DIR = .$$OPSYS-$$ARCH/ui
MOC_DIR = .$$OPSYS-$$ARCH/moc
OBJECTS_DIR = .$$OPSYS-$$ARCH/obj

!build_pass:message("Generating source for documentation")
!build_pass:system("doxygen doxygen.conf > /dev/null")
!build_pass:message("Building documentation")
!build_pass:system("make -C doc/latex > /dev/null")
!build_pass:system("cp doc/latex/refman.pdf .")
!build_pass:message("Documentation is available in refman.pdf")
