#include "QualitySourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QComboBox>

#include "QualityData.hpp"

#include "noise/noise.h"

//this node allows the user to set quality values used in noise generation
QualitySourceDataModel::QualitySourceDataModel(): _comboBox(new QComboBox())
{
  _comboBox->addItem("Fast");
  _comboBox->addItem("Standard");
  _comboBox->addItem("Best");

  connect(_comboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this, &QualitySourceDataModel::onComboEdited );

  _comboBox->setCurrentIndex(1);

}


QJsonObject QualitySourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void QualitySourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<QualityData>(d);
      _comboBox->setCurrentIndex(d);
    }
  }
}


unsigned int QualitySourceDataModel::nPorts(PortType portType) const
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


void QualitySourceDataModel::onComboEdited()
{
  int number = _comboBox->currentIndex();
  _number = std::make_shared<QualityData>(number);

  emit dataUpdated(0);
}


NodeDataType QualitySourceDataModel::dataType(PortType, PortIndex) const
{
  return QualityData().type();
}


std::shared_ptr<NodeData>QualitySourceDataModel::outData(PortIndex)
{
  return _number;
}
