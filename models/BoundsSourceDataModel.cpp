#include "BoundsSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "BoundsData.hpp"

#include "noise/noise.h"

BoundsSourceDataModel::BoundsSourceDataModel(): _spinBox(new QDoubleSpinBox())
{
  _spinBox->setRange(0.01,10000);
  _spinBox->setSingleStep(1);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BoundsSourceDataModel::onSpinEdited );

  _spinBox->setValue(noise::module::DEFAULT_PERLIN_FREQUENCY);

}


QJsonObject BoundsSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void BoundsSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<BoundsData>(d);
      _spinBox->setValue(d);
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


void BoundsSourceDataModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<BoundsData>(number);

  emit dataUpdated(0);
}


NodeDataType BoundsSourceDataModel::dataType(PortType, PortIndex) const
{
  return BoundsData().type();
}


std::shared_ptr<NodeData>BoundsSourceDataModel::outData(PortIndex)
{
  return _number;
}