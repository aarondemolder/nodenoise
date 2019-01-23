#pragma once

#include <QtCore/QObject>
#include <QComboBox>

#include <nodes/NodeDataModel>

#include <iostream>

class AutoGradientData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class LnAutoGradientModel : public NodeDataModel
{
  Q_OBJECT

public:
  LnAutoGradientModel();

  virtual
  ~LnAutoGradientModel() {}

public:

  QString caption() const override { return QStringLiteral("Auto Gradient"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Auto Gradient"); }

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

  std::shared_ptr<AutoGradientData> _number;

  QComboBox * _comboBox;

};
