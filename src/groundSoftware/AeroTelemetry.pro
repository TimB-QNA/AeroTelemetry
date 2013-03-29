TEMPLATE = app
LANGUAGE = C++

CONFIG  += qt warn_on release
QMAKE_CXXFLAGS += -Wno-deprecated
QT += xml network

DEFINES += TOLERANCE=1e-9 VERSION=QString\\\(\\\"pre-1.0-0\\\"\\\)

HEADERS += mainWindow.h \
           gfxDisplay.h \
           gfxObject.h \
           gfxRhino3D.h \
           gfxOSM.h gfxOSMnode.h gfxOSMway.h\
           modelData.h \
           settings.h \
           viewSettings.h \
           odPoint.h \
           odMatrix.h \
           pluginInterfaces.h \
           telemetryData.h \
           telemetryDataPoint.h \
           importDialog.h \
           selectModelDialog.h \
           navigationToolbar.h \
           projection.h \
           graphPlot.h \
           graphPlotOptions.h

SOURCES += main.cpp \
           mainWindow.cpp \
           gfxDisplay.cpp \
           gfxObject.cpp \
           gfxRhino3D.cpp \
           gfxOSM.cpp gfxOSMnode.cpp gfxOSMway.cpp\
           modelData.cpp \
           settings.cpp \
           viewSettings.cpp \
           odPoint.cpp \
           odMatrix.cpp \
           telemetryData.cpp \
           telemetryDataPoint.cpp \
           importDialog.cpp \
           selectModelDialog.cpp \
           navigationToolbar.cpp \
           projection.cpp \
           graphPlot.cpp \
           graphPlotOptions.cpp

INCLUDEPATH += /usr/include/vtk-5.8 \
               $$[QT_INSTALL_HEADERS]/OpenPilot

LIBS += -lqt4gnuplot
# VTK
LIBS += -L/usr/lib/vtk-5.8 -lQVTK -lvtkCommon -lvtksys -lvtkRendering
LIBS += -lvtkGraphics -lvtkFiltering


#Open NURBS
LIBS += openNURBS-5/libopenNURBS.a

ARCH  = $$system("uname -m")
OPSYS = $$system("uname")
DESTDIR = ../../bin-$$ARCH/

UI_DIR = .$$OPSYS-$$ARCH/ui
MOC_DIR = .$$OPSYS-$$ARCH/moc
OBJECTS_DIR = .$$OPSYS-$$ARCH/obj

!build_pass:message("Generating source for documentation")
!build_pass:system("doxygen doxygen.conf > /dev/null")
!build_pass:message("Building documentation")
!build_pass:system("make -C doc/latex > /dev/null")
!build_pass:system("cp doc/latex/refman.pdf .")
!build_pass:message("Documentation is available in refman.pdf")
