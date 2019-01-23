#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class ImageWriterModel : public NodeDataModel
{
  Q_OBJECT

public:
  ImageWriterModel();

  virtual
  ~ImageWriterModel() {}

public:

  QString caption() const override { return QString("Click to Save"); }

  QString name() const override { return QString("Image Writer"); }

public:

  virtual QString modelName() const { return QString("ImageWriterModel"); }

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;

  QWidget *embeddedWidget() override { return _label; }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;

private:

  QLabel * _label;

  std::shared_ptr<NodeData> _nodeData;
};
