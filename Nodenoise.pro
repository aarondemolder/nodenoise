TARGET=Nodenoise

#requires devtoolkit7 to be compiler on laptop
CONFIG += c++17

#CONFIG-=app_bundle
SOURCES += $$PWD/src/main.cpp \
                $$PWD/nodes/*.cpp \
                $$PWD/models/*.cpp

HEADERS+= $$PWD/include/TextData.hpp \
                $$PWD/include/PixmapData.hpp \
                $$PWD/include/PerlinData.hpp \
                $$PWD/include/TerrainData.hpp \
                $$PWD/include/QualityData.hpp \
                $$PWD/include/DecimalData.hpp \
                $$PWD/include/SeedData.hpp \
                $$PWD/include/FreqData.hpp \
                $$PWD/include/LacData.hpp \
                $$PWD/include/PerData.hpp \
                $$PWD/include/OctaveData.hpp \
                $$PWD/nodes/*.hpp \
                $$PWD/models/*.hpp

#OTHER_FILES+=$$PWD/tests/*.rib

QT+= core widgets gui opengl

INCLUDEPATH+=$$PWD/include \
                /home/ademolder/include
INCLUDEPATH+=$$PWD/nodes
INCLUDEPATH+=/home/ademolder/include

LIBS += -L/home/ademolder/lib -lnoise -lnoiseutils

#for compiling on the laptop build
LIBS += -L/usr/lib64/nvidia
LIBS += -L/home/aarondemolder/lib -lnoise -lnoiseutils
INCLUDEPATH+=$$PWD/include \
                /home/aarondemolder/include

DEFINES+=NODE_EDITOR_STATIC
MOC_DIR=$$PWD/moc
OBJECTS_DIR=$$PWD/obj
UI_HEADERS_DIR=$$PWD/include

#FORMS+=$$PWD/ui/ShaderParams.ui \
#    ui/MainWindow.ui

RESOURCES+= $$PWD/nodes/resources/resources.qrc


