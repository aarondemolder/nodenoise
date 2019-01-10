#include "OctaveSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "OctaveData.hpp"

#include <noise/noise.h>

OctaveSourceDataModel::OctaveSourceDataModel(): _spinBox(new QSpinBox())
{
  _spinBox->setRange(1,30);
  _spinBox->setSingleStep(1);
  connect(_spinBox, QOverload<const QString &>::of(&QSpinBox::valueChanged), this, &OctaveSourceDataModel::onSpinEdited );

  _spinBox->setValue(noise::module::DEFAULT_PERLIN_OCTAVE_COUNT);

}


QJsonObject OctaveSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void OctaveSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<OctaveData>(d);
      _spinBox->setValue(d);
    }
  }
}


unsigned int OctaveSourceDataModel::nPorts(PortType portType) const
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


void OctaveSourceDataModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<OctaveData>(number);

  emit dataUpdated(0);
}


NodeDataType OctaveSourceDataModel::dataType(PortType, PortIndex) const
{
  return OctaveData().type();
}


std::shared_ptr<NodeData>OctaveSourceDataModel::outData(PortIndex)
{
  return _number;
}
