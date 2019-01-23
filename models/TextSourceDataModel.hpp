#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QTextEdit>

#include "TextData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

//The class dictates the node settings and objects such as caption, number of inputs and outputs and more.
class TextSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  TextSourceDataModel();

  virtual
  ~TextSourceDataModel() {}

public:

  QString caption() const override { return QString("Notes"); }

  bool captionVisible() const override { return false; }

  static QString Name() { return QString("Notes"); }

  QString name() const override { return TextSourceDataModel::Name(); }

public:

  QJsonObject save() const override;

  void restore(QJsonObject const &p) override;

public:

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override { }

  QWidget *embeddedWidget() override { return _lineEdit; }

private slots:

  void onTextEdited();

private:

  QTextEdit * _lineEdit;

};
