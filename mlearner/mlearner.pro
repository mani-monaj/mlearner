SOURCES += $$PWD/tiles.cpp \
    $$PWD/eligibiltytrace.cpp \
    $$PWD/mtdlearnerbase.cpp \
    $$PWD/mtilelearnerbase.cpp \
    $$PWD/mtilesarsalearner.cpp \
    $$PWD/mtileqlearner.cpp \
    $$PWD/mfuzzylearnerbase.cpp \
    $$PWD/mfuzzyaclearner.cpp \
    $$PWD/mfuzzyqlearner.cpp
INCLUDEPATH += . \
    $$PWD/include
LIBS += -L$$PWD/libs \
    -ljfuzzyqt
HEADERS += $$PWD/tiles.hpp \
    $$PWD/eligibiltytrace.h \
    $$PWD/mtdlearnerbase.h \
    $$PWD/mtilelearnerbase.h \
    $$PWD/mtilesarsalearner.h \
    $$PWD/mtileqlearner.h \
    $$PWD/mfuzzylearnerbase.h \
    $$PWD/mfuzzyaclearner.h \
    $$PWD/mfuzzyqlearner.h

