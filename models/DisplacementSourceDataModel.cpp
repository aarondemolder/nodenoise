#include "DisplacementSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "DisplacementData.hpp"

#include "noise/noise.h"

//This node creates our displacement values for voronoi noise generation
//Create and set our frequency spinbox and values, connect this to allow emitting data
DisplacementSourceDataModel::DisplacementSourceDataModel(): _spinBox(new QDoubleSpinBox())
{
  //default values
  _spinBox->setRange(0.01,10000);
  _spinBox->setSingleStep(0.1);
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &DisplacementSourceDataModel::onSpinEdited );

  _spinBox->setValue(noise::module::DEFAULT_VORONOI_DISPLACEMENT);

}

//value saving
QJsonObject DisplacementSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}

//value restoring
void DisplacementSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<DisplacementData>(d);
      _spinBox->setValue(d);
    }
  }
}

//port configuration
unsigned int DisplacementSourceDataModel::nPorts(PortType portType) const
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
void DisplacementSourceDataModel::onSpinEdited()
{
  double number = _spinBox->value();
  _number = std::make_shared<DisplacementData>(number);

  emit dataUpdated(0);
}

//configure data output type
NodeDataType DisplacementSourceDataModel::dataType(PortType, PortIndex) const
{
  return DisplacementData().type();
}

//node data return
std::shared_ptr<NodeData>DisplacementSourceDataModel::outData(PortIndex)
{
  return _number;
}
