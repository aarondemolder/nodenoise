#include "BiasSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "BiasData.hpp"

#include "noise/noise.h"

//This node is our bias source value
//Create and set our bias spinbox and values, connect this to allow emitting data
BiasSourceDataModel::BiasSourceDataModel(): _spinBox(new QDoubleSpinBox())
{
  //set default values
  _spinBox->setRange(-10,10);
  _spinBox->setSingleStep(0.1);

  //conect
  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &BiasSourceDataModel::onSpinEdited );

  _spinBox->setValue(0.0);

}

//Value saving
QJsonObject BiasSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_bias) modelJson["bias"] = QString::number(_bias->bias());

  return modelJson;
}

//Value restoring if exists
void BiasSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["bias"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _bias = std::make_shared<BiasData>(d);
      _spinBox->setValue(d);
    }
  }
}

//Configure node ports
unsigned int BiasSourceDataModel::nPorts(PortType portType) const
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

//Emit new Bias value when spinbox value is changed
void BiasSourceDataModel::onSpinEdited()
{
  double bias = _spinBox->value();
  _bias = std::make_shared<BiasData>(bias);

  emit dataUpdated(0);
}

//Configure node output data type
NodeDataType BiasSourceDataModel::dataType(PortType, PortIndex) const
{
  return BiasData().type();
}

//Node data output
std::shared_ptr<NodeData>BiasSourceDataModel::outData(PortIndex)
{
  return _bias;
}
