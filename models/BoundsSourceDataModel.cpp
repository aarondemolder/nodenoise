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

BoundsSourceDataModel::BoundsSourceDataModel(): _boundsGroup(new QGroupBox(tr("Noise Bound Coords")))
{
    _boundsGroup->setAlignment(4);
    _boundsGroup->setTitle("X    -    Z");

    _lowerXBound = new QDoubleSpinBox();
    _upperXBound = new QDoubleSpinBox();
    _lowerZBound = new QDoubleSpinBox();
    _upperZBound = new QDoubleSpinBox();

    _lowerXBound->setValue(6.0);
    _upperXBound->setValue(10.0);
    _lowerZBound->setValue(1.0);
    _upperZBound->setValue(5.0);

    //NEED TO ADD VALUE CHECKS TO PREVENT BOUND SETTING EXCEPTIONS

    QHBoxLayout *vboxTop = new QHBoxLayout;

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(_lowerXBound);
    vbox1->addWidget(_upperXBound);
    vbox1->addStretch(1);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(_lowerZBound);
    vbox2->addWidget(_upperZBound);
    vbox2->addStretch(1);

    QVBoxLayout *vbox3 = new QVBoxLayout;
    QFrame *vLine = new QFrame();
    vLine->setFrameShape(QFrame::VLine);
    vLine->setFrameShadow(QFrame::Raised);

    vbox3->addWidget(vLine);
    //vbox3->addWidget(displayText);

    vboxTop->addLayout(vbox1);
    vboxTop->addLayout(vbox3);
    vboxTop->addLayout(vbox2);
    vboxTop->addStretch(2);
    _boundsGroup->setLayout(vboxTop);

    connect(_lowerXBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );
    connect(_upperXBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );

    connect(_lowerZBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );
    connect(_upperZBound, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onGroupEdited );

}


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


void BoundsSourceDataModel::onGroupEdited()
{
  double numberXL = _lowerXBound->value();
  double numberXU = _upperXBound->value();
  double numberZL = _lowerZBound->value();
  double numberZU = _upperZBound->value();
  _bounds = std::make_shared<BoundsData>(numberXL, numberXU, numberZL, numberZU);

  emit dataUpdated(0);
}


NodeDataType BoundsSourceDataModel::dataType(PortType, PortIndex) const
{
  return BoundsData().type();
}


std::shared_ptr<NodeData>BoundsSourceDataModel::outData(PortIndex)
{
  return _bounds;
}
