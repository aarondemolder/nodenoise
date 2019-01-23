#include "LnAutoGradientModel.hpp"

#include <QtCore/QJsonValue>
#include <QComboBox>

#include "AutoGradientData.hpp"

#include "noise/noise.h"

//This node allows the user to select a terrain renderer gradient type with a combobox
LnAutoGradientModel::LnAutoGradientModel(): _comboBox(new QComboBox())
{
  _comboBox->addItem("Build Grayscale Gradient");
  _comboBox->addItem("Build Terrain Gradient");

  connect(_comboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this, &LnAutoGradientModel::onComboEdited );

  _comboBox->setCurrentIndex(0);

}


QJsonObject LnAutoGradientModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void LnAutoGradientModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    int d = strNum.toInt(&ok);
    if (ok)
    {
      _number = std::make_shared<AutoGradientData>(d);
      _comboBox->setCurrentIndex(d);
    }
  }
}


unsigned int LnAutoGradientModel::nPorts(PortType portType) const
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


void LnAutoGradientModel::onComboEdited()
{
  int number = _comboBox->currentIndex();
  _number = std::make_shared<AutoGradientData>(number);

  emit dataUpdated(0);
}


NodeDataType LnAutoGradientModel::dataType(PortType, PortIndex) const
{
  return AutoGradientData().type();
}


std::shared_ptr<NodeData>LnAutoGradientModel::outData(PortIndex)
{
  return _number;
}
