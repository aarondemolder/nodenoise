#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QOpenGLWidget>

#include <nodes/DataModelRegistry>

//now we bring in all our node model headers

//Misc viewers
#include "models/TextSourceDataModel.hpp"
#include "models/ImageShowModel.hpp"
#include "models/ImageLoaderModel.hpp"
#include "models/ImageWriterModel.hpp"
#include "models/PreviewWriterModel.hpp"
#include "models/View3DModel.hpp"

//Generators & Value Inputs
#include "models/LnPerlinModel.hpp"
#include "models/LnBillowModel.hpp"
#include "models/LnRidgedMultiModel.hpp"
#include "models/FreqSourceDataModel.hpp"
#include "models/LacSourceDataModel.hpp"
#include "models/OctaveSourceDataModel.hpp"
#include "models/PerSourceDataModel.hpp"
#include "models/SeedSourceDataModel.hpp"
#include "models/QualitySourceDataModel.hpp"

//Heightmap Gen & Rendering
#include "models/LnHeightMapBuilder.hpp"
#include "models/ResolutionSourceDataModel.hpp"
#include "models/BoundsSourceDataModel.hpp"
#include "models/ImageRenderModel.hpp"
#include "models/LnLightBrightnessModel.hpp"
#include "models/LnLightContrastModel.hpp"
#include "models/LnAutoGradientModel.hpp"
#include "models/ColourSourceDataModel.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowView;
using QtNodes::FlowScene;
using QtNodes::ConnectionStyle;

static std::shared_ptr<DataModelRegistry>registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

  //register our data models to appear in the graph menu
  ret->registerModel<SeedSourceDataModel>("Generator Inputs");
  ret->registerModel<PerSourceDataModel>("Generator Inputs");
  ret->registerModel<OctaveSourceDataModel>("Generator Inputs");
  ret->registerModel<LacSourceDataModel>("Generator Inputs");
  ret->registerModel<FreqSourceDataModel>("Generator Inputs");
  ret->registerModel<LnRidgedMultiModel>("Generators");
  ret->registerModel<QualitySourceDataModel>("Generator Inputs");
  ret->registerModel<LnPerlinModel>("Generators");
  ret->registerModel<LnBillowModel>("Generators");

  ret->registerModel<LnHeightMapBuilder>("Heightmap Generation");
  ret->registerModel<ResolutionSourceDataModel>("Heightmap Generation");
  ret->registerModel<BoundsSourceDataModel>("Heightmap Generation");

  ret->registerModel<LnLightBrightnessModel>("Rendering");
  ret->registerModel<LnLightContrastModel>("Rendering");
  ret->registerModel<LnAutoGradientModel>("Rendering");
  ret->registerModel<ColourSourceDataModel>("Rendering");

  ret->registerModel<ImageShowModel>("Image");
  ret->registerModel<ImageLoaderModel>("Image");
  ret->registerModel<ImageWriterModel>("Image");
  ret->registerModel<ImageRenderModel>("Rendering");
  ret->registerModel<PreviewWriterModel>("Preview");


  ret->registerModel<TextSourceDataModel>("Notes");
  ret->registerModel<View3DModel>("Preview");

  ///scale bias needs work before being stable
  //ret->registerModel<LnScaleBiasModel>("libNoise");
  //ret->registerModel<BiasSourceDataModel>("libNoise");
  //ret->registerModel<ScaleSourceDataModel>("libNoise");

  return ret;
}

//We can set the graph styles
static void setStyle()
{
  ConnectionStyle::setConnectionStyle(
  R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  }
  )");
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  //all the bits to set the profile to allow QOpenGLWidget to work
  QSurfaceFormat format;
  format.setSamples(4);
  #if defined(__APPLE__)
      // at present mac osx Mountain Lion only supports GL3.2
      // the new mavericks will have GL 4.x so can change
      format.setMajorVersion(4);
      format.setMinorVersion(1);
  #else
      format.setMajorVersion(4);
      format.setMinorVersion(3);
  #endif
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);

  QSurfaceFormat::setDefaultFormat(format);

  setStyle();

  //add our widgets and menus
  QWidget mainWidget;

  auto menuBar    = new QMenuBar();
  auto saveAction = menuBar->addAction("Save..");
  auto loadAction = menuBar->addAction("Load..");
  auto clearAction = menuBar->addAction("Clear..");

  QVBoxLayout *l = new QVBoxLayout(&mainWidget);

  l->addWidget(menuBar);
  auto scene = new FlowScene(registerDataModels(), &mainWidget);
  l->addWidget(new FlowView(scene));
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  QObject::connect(saveAction, &QAction::triggered, scene, &FlowScene::save);
  QObject::connect(loadAction, &QAction::triggered, scene, &FlowScene::load);
  QObject::connect(clearAction, &QAction::triggered, scene, &FlowScene::clearScene);

  std::cout<<"Profile is "<<format.majorVersion()<<" "<<format.minorVersion()<<"\n";


  mainWidget.setWindowTitle("Terrain Generator");
  mainWidget.resize(800, 600);
  mainWidget.show();


  return app.exec();
}
