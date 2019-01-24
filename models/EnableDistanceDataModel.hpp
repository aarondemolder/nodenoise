#pragma once

#include <QtCore/QObject>
#include <QComboBox>

#include <nodes/NodeDataModel>

#include <iostream>

class EnableDistanceData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class EnableDistanceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  EnableDistanceDataModel();

  virtual
  ~EnableDistanceDataModel() {}

public:

  QString caption() const override { return QStringLiteral("Enable Distance"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Enable Distance"); }

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

  std::shared_ptr<EnableDistanceData> _number;

  QComboBox * _comboBox;

};
