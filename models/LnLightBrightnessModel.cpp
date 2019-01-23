#include "LnLightBrightnessModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "LightBrightnessData.hpp"

#include "noise/noise.h"

//This node sets the image renderer light brightness
LnLightBrightnessModel::LnLightBrightnessModel(): _spinBox(new QDoubleSpinBox())
{
  _spinBox->setRange(0.0,10);
  _spinBox->setSingleStep(0.1);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &LnLightBrightnessModel::onSpinEdited );

  _spinBox->setValue(2.0);

}


QJsonObject LnLightBrightnessModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void LnLightBrightnessModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<LightBrightnessData>(d);
      _spinBox->setValue(d);
    }
  }
}


unsigned int LnLightBrightnessModel::nPorts(PortType portType) const
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


void LnLightBrightnessModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<LightBrightnessData>(number);

  emit dataUpdated(0);
}


NodeDataType LnLightBrightnessModel::dataType(PortType, PortIndex) const
{
  return LightBrightnessData().type();
}


std::shared_ptr<NodeData>LnLightBrightnessModel::outData(PortIndex)
{
  return _number;
}
