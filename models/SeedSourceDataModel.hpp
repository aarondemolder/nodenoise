#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include <nodes/NodeDataModel>

#include <iostream>

#include <noise/noise.h>

class SeedData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class SeedSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  SeedSourceDataModel();

  virtual
  ~SeedSourceDataModel() {}

public:

  QString caption() const override { return QStringLiteral("Seed Source"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Seed Source"); }

public:

  QJsonObject save() const override;

  void restore(QJsonObject const &p) override;

public:

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override{ }

  QWidget *embeddedWidget() override { return _lineEdit; }

private slots:

  void onTextEdited(QString const &string);

private:

  std::shared_ptr<SeedData> _number;

  QLineEdit * _lineEdit;
};
