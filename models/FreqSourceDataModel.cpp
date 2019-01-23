#include "FreqSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "FreqData.hpp"

#include "noise/noise.h"

//This node creates our frequency values for noise generation
//Create and set our frequency spinbox and values, connect this to allow emitting data
FreqSourceDataModel::FreqSourceDataModel(): _spinBox(new QDoubleSpinBox())
{
  //default values
  _spinBox->setRange(0.01,10000);
  _spinBox->setSingleStep(1);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &FreqSourceDataModel::onSpinEdited );

  //even though we set default values using the perlin model, we should probably add options to load the default values for other generation types
  //this works for now, though
  _spinBox->setValue(noise::module::DEFAULT_PERLIN_FREQUENCY);

}

//value saving
QJsonObject FreqSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}

//value restoring
void FreqSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<FreqData>(d);
      _spinBox->setValue(d);
    }
  }
}

//port configuration
unsigned int FreqSourceDataModel::nPorts(PortType portType) const
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

//emit frequency output if value changed
void FreqSourceDataModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<FreqData>(number);

  emit dataUpdated(0);
}

//configure data output type
NodeDataType FreqSourceDataModel::dataType(PortType, PortIndex) const
{
  return FreqData().type();
}

//node data return
std::shared_ptr<NodeData>FreqSourceDataModel::outData(PortIndex)
{
  return _number;
}
