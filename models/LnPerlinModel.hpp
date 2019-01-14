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
class LnPerlinModel : public NodeDataModel
{
  Q_OBJECT

public:
  LnPerlinModel();

  void defaultImgRenderer();


  virtual
  ~LnPerlinModel() {}

public:

  QString caption() const override { return QString("Perlin Model"); }

  bool captionVisible() const override { return true; }

  static QString Name() { return QString("Perlin Noise Generator"); }

  QString name() const override { return LnPerlinModel::Name(); }

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
                return PerData().type();
            case 4:
                return SeedData().type();
            case 5:
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

    if (port == 1)return std::make_shared<TerrainData>(_myPerlinModule);

    if (port == 2) return std::make_shared<PixmapData>(_pixmap);
  }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;


private slots:

  void onPixmapEdited(QPixmap const &pixmap);


private:

  QLabel * _label;

  QPixmap _pixmap;

  QString _identifier = "perlin";

  noise::module::Perlin _myPerlinModule;


};
