#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>

#include <nodes/DataModelRegistry>

#include "models/TextSourceDataModel.hpp"
#include "models/NumberSourceDataModel.hpp"
#include "models/ImageShowModel.hpp"
#include "models/ImageLoaderModel.hpp"

#include "models/LnPerlinModel.hpp"
#include "models/FreqSourceDataModel.hpp"
#include "models/LacSourceDataModel.hpp"
#include "models/OctaveSourceDataModel.hpp"
#include "models/PerSourceDataModel.hpp"
#include "models/SeedSourceDataModel.hpp"
#include "models/QualitySourceDataModel.hpp"

#include "models/LnHeightMapBuilder.hpp"

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

  //libnoise nodes
  ret->registerModel<LnPerlinModel>("libNoise");
  ret->registerModel<QualitySourceDataModel>("libNoise");
  ret->registerModel<LnHeightMapBuilder>("libNoise");

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

  mainWidget.setWindowTitle("Terrain Generator");
  mainWidget.resize(800, 600);
  mainWidget.show();

  return app.exec();
}
