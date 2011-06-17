SOURCES += $$PWD/src/tiles.cpp \
    $$PWD/src/eligibiltytrace.cpp \
    $$PWD/src/mtdlearnerbase.cpp \
    $$PWD/src/mtilelearnerbase.cpp \
    $$PWD/src/mtilesarsalearner.cpp \
    $$PWD/src/mtileqlearner.cpp \
    $$PWD/src/mfuzzylearnerbase.cpp \
    $$PWD/src/mfuzzyaclearner.cpp \
    $$PWD/src/mfuzzyqlearner.cpp
INCLUDEPATH += . \
    $$PWD/include
LIBS += -L$$PWD/libs \
    -ljfuzzyqt
HEADERS += $$PWD/include/tiles.hpp \
    $$PWD/include/eligibiltytrace.h \
    $$PWD/include/mtdlearnerbase.h \
    $$PWD/include/mtilelearnerbase.h \
    $$PWD/include/mtilesarsalearner.h \
    $$PWD/include/mtileqlearner.h \
    $$PWD/include/mfuzzylearnerbase.h \
    $$PWD/include/mfuzzyaclearner.h \
    $$PWD/include/mfuzzyqlearner.h

