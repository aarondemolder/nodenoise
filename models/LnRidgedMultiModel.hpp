#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "TerrainData.hpp"
#include "IdentifierData.hpp"

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
class LnRidgedMultiModel : public NodeDataModel
{
  Q_OBJECT

public:
  LnRidgedMultiModel();

  void defaultImgRenderer();


  virtual
  ~LnRidgedMultiModel() {}

public:

  QString caption() const override { return QString("RidgedMulti Model"); }

  bool captionVisible() const override { return true; }

  static QString Name() { return QString("RidgedMulti Noise Generator"); }

  QString name() const override { return LnRidgedMultiModel::Name(); }

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
                return LacData().type();
            case 2:
                return OctaveData().type();
            case 3:
                return SeedData().type();
            case 4:
                return QualityData().type();
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

    if (port == 1)return std::make_shared<TerrainData>(_myRidgeModule);

    if (port == 2) return std::make_shared<PixmapData>(_pixmap);
  }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;


private slots:

  void onPixmapEdited(QPixmap const &pixmap);


private:

  QLabel * _label;

  QPixmap _pixmap;

  QString _identifier = "ridge";

  noise::module::RidgedMulti _myRidgeModule;


};
