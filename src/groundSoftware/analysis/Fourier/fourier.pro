TEMPLATE        = app
LANGUAGE        = C++

CONFIG =

HEADERS += dataset1d.h \
           dataset2d.h \
           fourier.h

SOURCES += dataset1d.cpp \
           dataset2d.cpp \
           fourier.cpp   \
           main.cpp
INCLUDEPATH += /home/timb/Code/fftw3.2.2/include
LIBS += -L /home/timb/Code/fftw3.2.2/lib -lfftw3