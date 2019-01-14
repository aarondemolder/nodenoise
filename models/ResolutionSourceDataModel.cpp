#include "ResolutionSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QComboBox>

#include "ResolutionData.hpp"

#include "noise/noise.h"

ResolutionSourceDataModel::ResolutionSourceDataModel(): _comboBox(new QComboBox())
{
  _comboBox->addItem("256x256");
  _comboBox->addItem("512x512");
  _comboBox->addItem("1024x1024");
  _comboBox->addItem("2048x2048");
  _comboBox->addItem("4096x4096");

  connect(_comboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this, &ResolutionSourceDataModel::onComboEdited );

  _comboBox->setCurrentIndex(1);

}


QJsonObject ResolutionSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void ResolutionSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<ResolutionData>(d);
      _comboBox->setCurrentIndex(d);
    }
  }
}


unsigned int ResolutionSourceDataModel::nPorts(PortType portType) const
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


void ResolutionSourceDataModel::onComboEdited()
{
  int number = _comboBox->currentIndex();
  _number = std::make_shared<ResolutionData>(number);

  emit dataUpdated(0);
}


NodeDataType ResolutionSourceDataModel::dataType(PortType, PortIndex) const
{
  return ResolutionData().type();
}


std::shared_ptr<NodeData>ResolutionSourceDataModel::outData(PortIndex)
{
  return _number;
}
