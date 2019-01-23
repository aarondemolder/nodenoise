#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "IdentifierData.hpp"
#include "TerrainData.hpp"
#include "HeightMapData.hpp"
#include "ResolutionData.hpp"
#include "BoundsData.hpp"

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <iostream>

#include <noise/noise.h>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;


//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class LnHeightMapBuilder : public NodeDataModel
{
  Q_OBJECT

public:
  LnHeightMapBuilder();


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


private:

  QLabel * _label;

  QString _idText;

  int _idSet = 0;

  utils::NoiseMapBuilderPlane _heightMapBuilder;

  utils::NoiseMap _heightMap;

  int _resSet = 0;

  int _resSize = 256;

  int _resolution = 256;

  int _boundSet = 0;

};
