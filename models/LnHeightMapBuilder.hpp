#pragma once

#include <QtCore/QObject>
//#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
//#include <QtWidgets/QTextEdit>

#include "IdentifierData.hpp"
#include "TerrainData.hpp"
#include "HeightMapData.hpp"
#include "ResolutionData.hpp"
#include "BoundsData.hpp"

#include "DecimalData.hpp"

#include "FreqData.hpp"
#include "LacData.hpp"
#include "OctaveData.hpp"
#include "PerData.hpp"
#include "SeedData.hpp"
#include "QualityData.hpp"

#include "PixmapData.hpp"

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <iostream>

#include <noise/noise.h>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;



/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class LnHeightMapBuilder : public NodeDataModel
{
  Q_OBJECT

public:
  LnHeightMapBuilder();

  //std::shared_ptr<noise::module::Perlin> myModule;

  virtual
  ~LnHeightMapBuilder() {}

public:

  QString caption() const override { return QString("HeightMap Builder"); }

  bool captionVisible() const override { return true; }

  static QString Name() { return QString("HeightMap Builder"); }

  QString name() const override { return LnHeightMapBuilder::Name(); }

public:

  unsigned int nPorts(PortType portType) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData> data, int) override;

  QWidget *embeddedWidget() override { return _label; }

  bool resizable() const override { return true; }

public:

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override
  {
    switch (portType)
    {
      case PortType::In:
        switch (portIndex)
        {
        case 0:
            return IdentifierData().type();
        case 1:
            return TerrainData().type();
        case 2:
            return ResolutionData().type();
        case 3:
            return BoundsData().type();
        }
        break;

    case PortType::Out:
      switch (portIndex)
      {
        case 0:
          return HeightMapData().type();
      }
      break;

    case PortType::None:
      break;

    }
    return NodeDataType();
  }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;

//public slots:

//  void updateTerrain(std::shared_ptr<noise::module::Perlin>);


private slots:

  void onTextEdited(QString const &string);



private:

  QLabel * _label;

  QString _idText;

  int _idSet = 0;

  utils::NoiseMapBuilderPlane _heightMapBuilder;

  int _resSet = 0;

  int _resSize = 256;

};
