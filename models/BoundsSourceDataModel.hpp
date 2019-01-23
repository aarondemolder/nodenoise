#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QTableWidget>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QFrame>

#include <nodes/NodeDataModel>

#include <iostream>

class BoundsData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class BoundsSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  BoundsSourceDataModel();

  virtual
  ~BoundsSourceDataModel() {}

public:

  QString caption() const override { return QStringLiteral("Bounds Source"); }

  bool captionVisible() const override { return false; }

  QString name() const override { return QStringLiteral("Bounds Source"); }

public:

  QJsonObject save() const override;

  void restore(QJsonObject const &p) override;

public:

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override{ }

  QWidget *embeddedWidget() override { return _boundsGroup; }

private slots:

  void onGroupEdited();

  void onCountEdited();

private:

  std::shared_ptr<BoundsData> _bounds;

  QGroupBox *_boundsGroup;


  QDoubleSpinBox *_lowerXBound;

  QDoubleSpinBox *_upperXBound;


  QDoubleSpinBox *_lowerZBound;

  QDoubleSpinBox *_upperZBound;

  QDoubleSpinBox *_coherenceCount;



};
