#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QGroupBox>


#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

#include "glwidget.h"



using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;



/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class View3DModel : public NodeDataModel
{
  Q_OBJECT

public:

  View3DModel();

  virtual
  ~View3DModel() {}

public:

  QString caption() const override { return QString("3D Viewer"); }

  QString name() const override { return QString("3D Viewer"); }

public:

  virtual QString modelName() const { return QString("View3DModel"); }

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;

  QWidget *embeddedWidget() override { return _view3d; }

  bool resizable() const override { return true; }



protected:

  //bool eventFilter(QObject *object, QEvent *event) override;

private:

  GLWidget * _view3d;

  std::shared_ptr<NodeData> _nodeData;


};



