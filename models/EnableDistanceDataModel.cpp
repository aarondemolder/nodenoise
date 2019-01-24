#include "EnableDistanceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QComboBox>

#include "EnableDistanceData.hpp"

#include "noise/noise.h"

//This node allows the user to enable distance generation for voronoi
EnableDistanceDataModel::EnableDistanceDataModel(): _comboBox(new QComboBox())
{
  _comboBox->addItem("Distance Disabled");
  _comboBox->addItem("Distance Enabled");

  connect(_comboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this, &EnableDistanceDataModel::onComboEdited );

  _comboBox->setCurrentIndex(0);

}


QJsonObject EnableDistanceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void EnableDistanceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    int d = strNum.toInt(&ok);
    if (ok)
    {
      _number = std::make_shared<EnableDistanceData>(d);
      _comboBox->setCurrentIndex(d);
    }
  }
}


unsigned int EnableDistanceDataModel::nPorts(PortType portType) const
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


void EnableDistanceDataModel::onComboEdited()
{
  int number = _comboBox->currentIndex();
  _number = std::make_shared<EnableDistanceData>(number);

  emit dataUpdated(0);
}


NodeDataType EnableDistanceDataModel::dataType(PortType, PortIndex) const
{
  return EnableDistanceData().type();
}


std::shared_ptr<NodeData>EnableDistanceDataModel::outData(PortIndex)
{
  return _number;
}
