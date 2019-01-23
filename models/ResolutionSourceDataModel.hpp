#pragma once

#include <QtCore/QObject>
#include <QComboBox>

#include <nodes/NodeDataModel>

#include <iostream>

class ResolutionData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class ResolutionSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  ResolutionSourceDataModel();

  virtual
  ~ResolutionSourceDataModel() {}

public:

  QString caption() const override { return QStringLiteral("Resolution Source"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Resolution Source"); }

public:

  QJsonObject save() const override;

  void restore(QJsonObject const &p) override;

public:

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override{ }

  QWidget *embeddedWidget() override { return _comboBox; }

private slots:

  void onComboEdited();

private:

  std::shared_ptr<ResolutionData> _number;

  QComboBox * _comboBox;

};
