#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

#include "PixmapData.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class PreviewWriterModel : public NodeDataModel
{
  Q_OBJECT

public:
  PreviewWriterModel();

  virtual
  ~PreviewWriterModel() {}

public:

  QString caption() const override { return QString("Preview Link"); }

  QString name() const override { return QString("Preview Link"); }

public:

  virtual QString modelName() const { return QString("PreviewWriterModel"); }

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override
  {
    switch (portType)
    {
      case PortType::In:
        switch (portIndex)
        {
            case 0:
                return PixmapData().type();
            case 1:
                return PixmapData().type();
        }
        break;

    case PortType::Out:
      switch (portIndex)
      {
        //
      }
      break;

    case PortType::None:
      break;

    }
    return NodeDataType();
  }


  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;

  QWidget *embeddedWidget() override { return _label; }


private:

  QLabel * _label;

  std::shared_ptr<NodeData> _nodeData;
};
