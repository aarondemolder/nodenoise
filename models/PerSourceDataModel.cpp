#include "PerSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "PerData.hpp"

#include "noise/noise.h"

PerSourceDataModel::PerSourceDataModel(): _spinBox(new QDoubleSpinBox())
{
  _spinBox->setRange(0.0,1.0);
  _spinBox->setSingleStep(0.1);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &PerSourceDataModel::onSpinEdited );

  _spinBox->setValue(noise::module::DEFAULT_PERLIN_PERSISTENCE);

}


QJsonObject PerSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void PerSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<PerData>(d);
      _spinBox->setValue(d);
    }
  }
}


unsigned int PerSourceDataModel::nPorts(PortType portType) const
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


void PerSourceDataModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<PerData>(number);

  emit dataUpdated(0);
}


NodeDataType PerSourceDataModel::dataType(PortType, PortIndex) const
{
  return PerData().type();
}


std::shared_ptr<NodeData>PerSourceDataModel::outData(PortIndex)
{
  return _number;
}
