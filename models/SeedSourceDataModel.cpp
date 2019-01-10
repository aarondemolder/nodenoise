#include "SeedSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "SeedData.hpp"

#include "noise/noise.h"

SeedSourceDataModel::SeedSourceDataModel(): _lineEdit(new QLineEdit())
{
  _lineEdit->setValidator(new QDoubleValidator());
  _lineEdit->setMaximumSize(_lineEdit->sizeHint());
  connect(_lineEdit, &QLineEdit::textChanged,this, &SeedSourceDataModel::onTextEdited);
  _lineEdit->setText("0");
}


QJsonObject SeedSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number) modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void SeedSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<SeedData>(d);
      _lineEdit->setText(strNum);
    }
  }
}


unsigned int SeedSourceDataModel::nPorts(PortType portType) const
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


void SeedSourceDataModel::onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  bool ok = false;

  double number = _lineEdit->text().toDouble(&ok);

  if (ok)
  {
    _number = std::make_shared<SeedData>(number);

    emit dataUpdated(0);
  }
  else
  {
    emit dataInvalidated(0);
  }
}


NodeDataType SeedSourceDataModel::dataType(PortType, PortIndex) const
{
  return SeedData().type();
}


std::shared_ptr<NodeData>SeedSourceDataModel::outData(PortIndex)
{
  return _number;
}
