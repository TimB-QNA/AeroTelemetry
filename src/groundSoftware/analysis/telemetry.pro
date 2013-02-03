TEMPLATE	= app
LANGUAGE	= C++

QT += network phonon xml

CONFIG  += qt warn_on release

HEADERS += mainWindow.h \
           videoDisplay.h \
           importDialog.h \
           telemetryData.h \
           telemetryDataPoint.h \
           mdiPlot.h \
           mdiPlotOptions.h \
           statisticsDisplay.h

SOURCES += main.cpp \
           mainWindow.cpp \
           videoDisplay.cpp \
           importDialog.cpp \
           telemetryData.cpp \
           telemetryDataPoint.cpp \
           mdiPlot.cpp \
           mdiPlotOptions.cpp \
           statisticsDisplay.cpp

LIBS += -lqt4gnuplot

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/OpenPilot

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

win32{
# Only needed for development purposes
# Probably handy to leave in though,
# as we tend to dump a lot of output to the console.
CONFIG += console
}
