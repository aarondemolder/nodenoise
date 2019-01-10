#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QDoubleSpinBox>

#include <nodes/NodeDataModel>

#include <iostream>

class PerData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class PerSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  PerSourceDataModel();

  virtual
  ~PerSourceDataModel() {}

public:

  QString caption() const override { return QStringLiteral("Persistence Source"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Persistence Source"); }

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

  std::shared_ptr<PerData> _number;

  QDoubleSpinBox * _spinBox;
};
