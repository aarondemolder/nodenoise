#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "TerrainData.hpp"
#include "IdentifierData.hpp"

#include "FreqData.hpp"
#include "SeedData.hpp"
#include "EnableDistanceData.hpp"
#include "DisplacementData.hpp"

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


//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class LnVoronoiModel : public NodeDataModel
{
  Q_OBJECT

public:
  LnVoronoiModel();

  void defaultImgRenderer();


  virtual
  ~LnVoronoiModel() {}

public:

  QString caption() const override { return QString("Voronoi Model"); }

  bool captionVisible() const override { return true; }

  static QString Name() { return QString("Voronoi Noise Generator"); }

  QString name() const override { return LnVoronoiModel::Name(); }

public:

  unsigned int nPorts(PortType portType) const override;

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
                return FreqData().type();
            case 1:
                return SeedData().type();
            case 2:
                return EnableDistanceData().type();
            case 3:
                return DisplacementData().type();
        }
        break;

    case PortType::Out:
      switch (portIndex)
      {
        case 0:
          return IdentifierData().type();
        case 1:
          return TerrainData().type();
        case 2:
          return PixmapData().type();
      }
      break;

    case PortType::None:
      break;

    }
    return NodeDataType();
  }

  std::shared_ptr<NodeData>outData(PortIndex port) override
  {
    if (port == 0)return std::make_shared<IdentifierData>(_identifier);

    if (port == 1)return std::make_shared<TerrainData>(_myVoronoiModule);

    if (port == 2) return std::make_shared<PixmapData>(_pixmap);
  }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;


private slots:

  void onPixmapEdited(QPixmap const &pixmap);


private:

  QLabel * _label;

  QPixmap _pixmap;

  QString _identifier = "voronoi";

  noise::module::Voronoi _myVoronoiModule;


};
