#include "LnLightContrastModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "LightContrastData.hpp"

#include "noise/noise.h"

LnLightContrastModel::LnLightContrastModel(): _spinBox(new QDoubleSpinBox())
{
  _spinBox->setRange(0.1,10);
  _spinBox->setSingleStep(0.1);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &LnLightContrastModel::onSpinEdited );

  _spinBox->setValue(1.0);

}


QJsonObject LnLightContrastModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void LnLightContrastModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<LightContrastData>(d);
      _spinBox->setValue(d);
    }
  }
}


unsigned int LnLightContrastModel::nPorts(PortType portType) const
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


void LnLightContrastModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<LightContrastData>(number);

  emit dataUpdated(0);
}


NodeDataType LnLightContrastModel::dataType(PortType, PortIndex) const
{
  return LightContrastData().type();
}


std::shared_ptr<NodeData>LnLightContrastModel::outData(PortIndex)
{
  return _number;
}
