#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QOpenGLWidget>

#include <nodes/DataModelRegistry>

//Misc viewers
#include "models/TextSourceDataModel.hpp"
#include "models/NumberSourceDataModel.hpp"
#include "models/ImageShowModel.hpp"
#include "models/ImageLoaderModel.hpp"
#include "models/ImageWriterModel.hpp"
#include "models/View3DModel.hpp"

//Generators
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

#include"models/MultiInputModel.hpp"


using QtNodes::DataModelRegistry;
using QtNodes::FlowView;
using QtNodes::FlowScene;
using QtNodes::ConnectionStyle;

static std::shared_ptr<DataModelRegistry>registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

  //Models display from bottom to top in gui list

  //notes node
  ret->registerModel<TextSourceDataModel>("Text");

  ret->registerModel<View3DModel>("3D");

  //number input
  //ret->registerModel<NumberSourceDataModel>("Number");
  ret->registerModel<SeedSourceDataModel>("Number");
  ret->registerModel<PerSourceDataModel>("Number");
  ret->registerModel<OctaveSourceDataModel>("Number");
  ret->registerModel<LacSourceDataModel>("Number");
  ret->registerModel<FreqSourceDataModel>("Number");

  //image nodes
  ret->registerModel<ImageShowModel>("Image");
  ret->registerModel<ImageLoaderModel>("Image");
  ret->registerModel<ImageWriterModel>("Image");
  ret->registerModel<ImageRenderModel>("libNoise");


  //libnoise nodes
  ret->registerModel<LnPerlinModel>("libNoise");
  ret->registerModel<LnBillowModel>("libNoise");
  ret->registerModel<LnRidgedMultiModel>("libNoise");
  ret->registerModel<QualitySourceDataModel>("libNoise");
  ret->registerModel<LnHeightMapBuilder>("libNoise");
  ret->registerModel<ResolutionSourceDataModel>("libNoise");
  ret->registerModel<BoundsSourceDataModel>("libNoise");

  ret->registerModel<LnLightBrightnessModel>("libNoise");
  ret->registerModel<LnLightContrastModel>("libNoise");
  ret->registerModel<LnAutoGradientModel>("libNoise");
  ret->registerModel<ColourSourceDataModel>("libNoise");

  //ret->registerModel<NaiveDataModel>();

  return ret;
}

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

  QWidget mainWidget;

  auto menuBar    = new QMenuBar();
  auto saveAction = menuBar->addAction("Save..");
  auto loadAction = menuBar->addAction("Load..");

  QVBoxLayout *l = new QVBoxLayout(&mainWidget);

  l->addWidget(menuBar);
  auto scene = new FlowScene(registerDataModels(), &mainWidget);
  l->addWidget(new FlowView(scene));
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  QObject::connect(saveAction, &QAction::triggered, scene, &FlowScene::save);
  QObject::connect(loadAction, &QAction::triggered, scene, &FlowScene::load);

  std::cout<<"Profile is "<<format.majorVersion()<<" "<<format.minorVersion()<<"\n";


  mainWidget.setWindowTitle("Terrain Generator");
  mainWidget.resize(800, 600);
  mainWidget.show();


  return app.exec();
}
