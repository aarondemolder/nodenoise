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

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ImageLoaderModel : public NodeDataModel
{
  Q_OBJECT

public:
  ImageLoaderModel();

  virtual
  ~ImageLoaderModel() {}

public:

  QString caption() const override { return QString("Image Loader"); }

  QString name() const override { return QString("Load Image"); }

public:

  virtual QString modelName() const { return QString("ImageLoaderModel"); }

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override { }

  QWidget *embeddedWidget() override { return _label; }

  bool resizable() const override { return true; }


//public:

//  QJsonObject
//  save() const override;

//  void
//  restore(QJsonObject const &p) override;


protected:

  bool eventFilter(QObject *object, QEvent *event) override;

private:

  QLabel * _label;

  QPixmap _pixmap;
};
