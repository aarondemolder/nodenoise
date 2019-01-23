#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "HeightMapData.hpp"
#include "ResolutionData.hpp"
#include "BoundsData.hpp"
#include "LightBrightnessData.hpp"
#include "LightContrastData.hpp"
#include "AutoGradientData.hpp"
#include "ColourData.hpp"

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
class ImageRenderModel : public NodeDataModel
{
  Q_OBJECT

public:
  ImageRenderModel();

  virtual
  ~ImageRenderModel() {}

public:

  QString caption() const override { return QString("Image Renderer"); }

  bool captionVisible() const override { return true; }

  static QString Name() { return QString("Image Renderer"); }

  QString name() const override { return ImageRenderModel::Name(); }

public:

  unsigned int nPorts(PortType portType) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData> data, int) override;

  QWidget *embeddedWidget() override { return _label; }

  bool resizable() const override { return true; }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;

public:

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override
  {
    switch (portType)
    {
      case PortType::In:
        switch (portIndex)
        {
        case 0:
            return HeightMapData().type();
        case 1:
            return LightBrightnessData().type();
        case 2:
            return LightContrastData().type();
        case 3:
            return ColourData().type();
        case 4:
            return AutoGradientData().type();
        }
        break;

    case PortType::Out:
      switch (portIndex)
      {
        case 0:
          return PixmapData().type();
      }
      break;

    case PortType::None:
      break;

    }
    return NodeDataType();
  }



private:

  QLabel * _label;

  QPixmap _pixmap;

  QColor _colour;

  utils::NoiseMap _heightMap;

  utils::NoiseMapBuilderPlane _heightMapBuilder;

  int _resolution = 256;

  int _resolutionSet = 0;

  int _heightMapSet = 0;

  utils::RendererImage renderer;

  utils::Image image;


};
