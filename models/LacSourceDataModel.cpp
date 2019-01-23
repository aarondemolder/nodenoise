#include "LacSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "LacData.hpp"

#include "noise/noise.h"

//This node creates our LACUNARITY values for noise generation
LacSourceDataModel::LacSourceDataModel(): _spinBox(new QDoubleSpinBox())
{
  _spinBox->setRange(1.5, 3.5);
  _spinBox->setSingleStep(0.01);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &LacSourceDataModel::onSpinEdited );

  _spinBox->setValue(noise::module::DEFAULT_PERLIN_LACUNARITY);

}


QJsonObject LacSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void LacSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<LacData>(d);
      _spinBox->setValue(d);
    }
  }
}


unsigned int LacSourceDataModel::nPorts(PortType portType) const
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


void LacSourceDataModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<LacData>(number);

  emit dataUpdated(0);
}


NodeDataType LacSourceDataModel::dataType(PortType, PortIndex) const
{
  return LacData().type();
}


std::shared_ptr<NodeData>LacSourceDataModel::outData(PortIndex)
{
  return _number;
}
