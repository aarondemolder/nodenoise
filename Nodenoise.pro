TARGET=Nodenoise

#requires devtoolkit7 to be compiler on laptop
CONFIG += c++17

QT+= core widgets gui opengl


#CONFIG-=app_bundle
SOURCES += $$PWD/src/main.cpp \
                $$PWD/nodes/*.cpp \
                $$PWD/models/*.cpp \
                $$PWD/src/glwidget.cpp \
                #$$PWD/src/glwindow.cpp \
                #$$PWD/src/glmainwindow.cpp \
                $$PWD/src/logo.cpp

HEADERS+= $$PWD/include/TextData.hpp \
                $$PWD/include/PixmapData.hpp \
                $$PWD/include/IdentifierData.hpp \
                $$PWD/include/TerrainData.hpp \
                $$PWD/include/HeightMapData.hpp \
                $$PWD/include/ResolutionData.hpp \
                $$PWD/include/BoundsData.hpp \
                $$PWD/include/QualityData.hpp \
                $$PWD/include/DecimalData.hpp \
                $$PWD/include/SeedData.hpp \
                $$PWD/include/FreqData.hpp \
                $$PWD/include/LacData.hpp \
                $$PWD/include/PerData.hpp \
                $$PWD/include/OctaveData.hpp \
                $$PWD/include/LightContrastData.hpp \
                $$PWD/include/LightBrightnessData.hpp \
                $$PWD/include/AutoGradientData.hpp \
                $$PWD/include/ColourData.hpp \
                $$PWD/include/ScaleData.hpp \
                $$PWD/include/BiasData.hpp \
                $$PWD/nodes/*.hpp \
                $$PWD/models/*.hpp \
                $$PWD/include/glwidget.h \
                #$$PWD/include/glwindow.h \
                #$$PWD/include/glmainwindow.h \
                $$PWD/include/logo.h


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

#end options for laptop build

DEFINES+=NODE_EDITOR_STATIC
MOC_DIR=$$PWD/moc
OBJECTS_DIR=$$PWD/obj
UI_HEADERS_DIR=$$PWD/include

RESOURCES+= $$PWD/nodes/resources/resources.qrc

#NGL Seems to conflict with the node framework, gl3w related
#NGLPATH=$$(NGLDIR)
#isEmpty(NGLPATH){
#        message("including $HOME/NGL")
#        include($(HOME)/NGL/UseNGL.pri)
#}
#else{
#        message("Using custom NGL location")
#        include($(NGLDIR)/UseNGL.pri)
#}
