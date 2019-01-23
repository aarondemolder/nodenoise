#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QColor>
#include <QColorDialog>
#include <QEvent>

#include <nodes/NodeDataModel>

#include <iostream>

class ColourData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class ColourSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  ColourSourceDataModel();

  virtual
  ~ColourSourceDataModel() {}

public:

  QString caption() const override { return QStringLiteral("Colour Source"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Colour Source"); }

public:

  QJsonObject save() const override;

  void restore(QJsonObject const &p) override;

public:

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override{ }

  QWidget *embeddedWidget() override { return _label; }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;

private:

  std::shared_ptr<ColourData> _colour;

  QLabel * _label;
};
