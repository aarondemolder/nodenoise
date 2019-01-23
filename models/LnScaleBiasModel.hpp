#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "IdentifierData.hpp"
#include "TerrainData.hpp"
#include "HeightMapData.hpp"
#include "ResolutionData.hpp"
#include "BoundsData.hpp"

#include "BiasData.hpp"
#include "ScaleData.hpp"

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


//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class LnScaleBiasModel : public NodeDataModel
{
  Q_OBJECT

public:
  LnScaleBiasModel();

  virtual
  ~LnScaleBiasModel() {}

public:

  QString caption() const override { return QString("Scale Bias"); }

  bool captionVisible() const override { return true; }

  static QString Name() { return QString("Scale Bias"); }

  QString name() const override { return LnScaleBiasModel::Name(); }

public:

  unsigned int nPorts(PortType portType) const override;

  //std::shared_ptr<NodeData> outData(PortIndex port) override;

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
            return BiasData().type();
        case 3:
            return ScaleData().type();
        }
        break;

    case PortType::Out:
      switch (portIndex)
      {
        case 0:
          return IdentifierData().type();
      case 1:
        return TerrainData().type();
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

    if (port == 1)return std::make_shared<TerrainData>(_myScaleModule);

    //if (port == 2) return std::make_shared<PixmapData>(_pixmap);
  }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;


private slots:

  void onTextEdited(QString const &string);


private:

  QLabel * _label;

  QPixmap _pixmap;

  QString _identifier = "scale";

  noise::module::ScaleBias _myScaleModule;

  double _bias;

  double _scale;

};
