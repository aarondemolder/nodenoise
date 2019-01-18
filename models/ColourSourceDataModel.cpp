#include "ColourSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "ColourData.hpp"

#include "noise/noise.h"

ColourSourceDataModel::ColourSourceDataModel(): _label(new QLabel("Colour Selector"))
{

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);
    _label->installEventFilter(this);


//  _spinBox->setRange(0.01,10000);
//  _spinBox->setSingleStep(1);
//  connect(_spinBox, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this, &ColourSourceDataModel::onSpinEdited );

//  _spinBox->setValue(noise::module::DEFAULT_PERLIN_FREQUENCY);

}


//QJsonObject ColourSourceDataModel::save() const
//{
//  QJsonObject modelJson = NodeDataModel::save();

//  if (_colour) modelJson["number"] = QColor::getRgbF(_colour->colour());

//  return modelJson;
//}


//void ColourSourceDataModel::restore(QJsonObject const &p)
//{
//  QJsonValue v = p["number"];

//  if (!v.isUndefined())
//  {
//    QString strNum = v.toString();

//    bool   ok;
//    double d = strNum.toDouble(&ok);
//    if (ok)
//    {
//      _colour = std::make_shared<ColourData>(d);
//      _spinBox->setValue(d);
//    }
//  }
//}


unsigned int ColourSourceDataModel::nPorts(PortType portType) const
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

bool ColourSourceDataModel::eventFilter(QObject *object, QEvent *event)
{


    if (object == _label)
    {

      if (event->type() == QEvent::MouseButtonPress)
      {

          //open colour dialog
        return true;
      }
    }

  return false;
}


void ColourSourceDataModel::onSpinEdited()
{
  double colour = _spinBox->value();
  _colour = std::make_shared<ColourData>(colour);

  emit dataUpdated(0);
}


NodeDataType ColourSourceDataModel::dataType(PortType, PortIndex) const
{
  return ColourData().type();
}


std::shared_ptr<NodeData>ColourSourceDataModel::outData(PortIndex)
{
  return _colour;
}
