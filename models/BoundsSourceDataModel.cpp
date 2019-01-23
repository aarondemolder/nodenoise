#include "BoundsSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QVBoxLayout>

#include "BoundsData.hpp"

#include "noise/noise.h"

//This node is our noise generation bounds source
//Create and set our bounds spinboxes within a Group
BoundsSourceDataModel::BoundsSourceDataModel(): _boundsGroup(new QGroupBox(tr("Noise Bound Coords")))
{
    //main group titles
    _boundsGroup->setAlignment(4);
    _boundsGroup->setTitle("X    -    Z");

    //create spinboxes
    _lowerXBound = new QDoubleSpinBox();
    _upperXBound = new QDoubleSpinBox();
    _lowerZBound = new QDoubleSpinBox();
    _upperZBound = new QDoubleSpinBox();

    //new layout to combine widgets
    QHBoxLayout *vboxTop = new QHBoxLayout;

    //X value widgets
    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(_lowerXBound);
    vbox1->addWidget(_upperXBound);
    vbox1->addStretch(1);

    //Z value widgets
    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(_lowerZBound);
    vbox2->addWidget(_upperZBound);
    vbox2->addStretch(1);

    //Divide widgets with a line
    QVBoxLayout *vbox3 = new QVBoxLayout;
    QFrame *vLine = new QFrame();
    vLine->setFrameShape(QFrame::VLine);
    vLine->setFrameShadow(QFrame::Raised);
    vbox3->addWidget(vLine);

    //Create spinbox to basically quickly skip through the coherent noise bounds
    _coherenceCount = new QDoubleSpinBox();

    _coherenceCount->setValue(0.0);
    _coherenceCount->setSingleStep(5.0);

    //set values
    _lowerXBound->setValue(0.0);
    _upperXBound->setValue(5.0);
    _lowerZBound->setValue(1.0+_coherenceCount->value());
    _upperZBound->setValue(6.0+_coherenceCount->value());

    //add extra spinbox to layout
    QVBoxLayout *vbox4 = new QVBoxLayout;
    vbox4->addWidget(_coherenceCount);

    //add layouts to group
    vboxTop->addLayout(vbox1);
    vboxTop->addLayout(vbox3);
    vboxTop->addLayout(vbox2);
    vboxTop->addLayout(vbox4);
    vboxTop->addStretch(2);
    _boundsGroup->setLayout(vboxTop);

    //connect all the spinboxes to appropriate functions
    connect(_coherenceCount, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onCountEdited );

    connect(_lowerXBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );
    connect(_upperXBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );

    connect(_lowerZBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );
    connect(_upperZBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );

}

//Save spinbox values - should probably save coherence value
QJsonObject BoundsSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_bounds)
  {
      modelJson["numberXL"] = QString::number(_bounds->numberXL());
      modelJson["numberXU"] = QString::number(_bounds->numberXU());
      modelJson["numberZL"] = QString::number(_bounds->numberZL());
      modelJson["numberZU"] = QString::number(_bounds->numberZU());
  }

  return modelJson;
}

//restore spinbox values
void BoundsSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v1 = p["numberXL"];
  QJsonValue v2 = p["numberXU"];
  QJsonValue v3 = p["numberZL"];
  QJsonValue v4 = p["numberZU"];

  if (!v1.isUndefined())
  {
    QString strNum1 = v1.toString();
    QString strNum2 = v2.toString();
    QString strNum3 = v3.toString();
    QString strNum4 = v4.toString();

    bool   ok;
    double d1 = strNum1.toDouble(&ok);
    double d2 = strNum2.toDouble(&ok);
    double d3 = strNum3.toDouble(&ok);
    double d4 = strNum4.toDouble(&ok);
    if (ok)
    {
      _bounds = std::make_shared<BoundsData>(d1,d2,d3,d4);
      _lowerXBound->setValue(d1);
      _upperXBound->setValue(d2);
      _lowerZBound->setValue(d3);
      _upperZBound->setValue(d4);
    }
  }
}

//configure ports
unsigned int BoundsSourceDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}

//when coherence count is edited update spin boxes and emit
void BoundsSourceDataModel::onCountEdited()
{
    _lowerZBound->setValue(1.0+_coherenceCount->value());
    _upperZBound->setValue(6.0+_coherenceCount->value());

    double numberXL = _lowerXBound->value();
    double numberXU = _upperXBound->value();
    double numberZL = _lowerZBound->value();
    double numberZU = _upperZBound->value();

    _bounds = std::make_shared<BoundsData>(numberXL, numberXU, numberZL, numberZU);
    emit dataUpdated(0);
}

//when spinboxes are edited, emit
void BoundsSourceDataModel::onGroupEdited()
{
  double numberXL = _lowerXBound->value();
  double numberXU = _upperXBound->value();
  double numberZL = _lowerZBound->value();
  double numberZU = _upperZBound->value();
  _bounds = std::make_shared<BoundsData>(numberXL, numberXU, numberZL, numberZU);

  emit dataUpdated(0);
}

//Configure node output data type
NodeDataType BoundsSourceDataModel::dataType(PortType, PortIndex) const
{
  return BoundsData().type();
}

//node data output
std::shared_ptr<NodeData>BoundsSourceDataModel::outData(PortIndex)
{
  return _bounds;
}
