#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QDoubleSpinBox>

#include <nodes/NodeDataModel>

#include <iostream>

class BiasData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class BiasSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  BiasSourceDataModel();

  virtual
  ~BiasSourceDataModel() {}

public:

  QString caption() const override { return QStringLiteral("Bias Source"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Bias Source"); }

public:

  QJsonObject save() const override;

  void restore(QJsonObject const &p) override;

public:

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override{ }

  QWidget *embeddedWidget() override { return _spinBox; }

private slots:

  void onSpinEdited();

private:

  std::shared_ptr<BiasData> _bias;

  QDoubleSpinBox * _spinBox;
};
