#include "ScaleSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "ScaleData.hpp"

#include "noise/noise.h"

ScaleSourceDataModel::ScaleSourceDataModel(): _spinBox(new QDoubleSpinBox())
{
  _spinBox->setRange(-100,100);
  _spinBox->setSingleStep(1);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &ScaleSourceDataModel::onSpinEdited );

  _spinBox->setValue(0.0);

}


QJsonObject ScaleSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_scale) modelJson["scale"] = QString::number(_scale->scale());

  return modelJson;
}


void ScaleSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["scale"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _scale = std::make_shared<ScaleData>(d);
      _spinBox->setValue(d);
    }
  }
}


unsigned int ScaleSourceDataModel::nPorts(PortType portType) const
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


void ScaleSourceDataModel::onSpinEdited()
{
  double scale = _spinBox->value();
  _scale = std::make_shared<ScaleData>(scale);

  emit dataUpdated(0);
}


NodeDataType ScaleSourceDataModel::dataType(PortType, PortIndex) const
{
  return ScaleData().type();
}


std::shared_ptr<NodeData>ScaleSourceDataModel::outData(PortIndex)
{
  return _scale;
}
