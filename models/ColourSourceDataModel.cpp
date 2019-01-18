#include "ColourSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "ColourData.hpp"

#include "noise/noise.h"

ColourSourceDataModel::ColourSourceDataModel(): _label(new QLabel("Click to select"))
{

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    _label->setAutoFillBackground(true);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);
    _label->installEventFilter(this);

}


QJsonObject ColourSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  //Should probably fix colour saving
  //if (_colour) modelJson["colour"] = QColor::name(_colour);

  return modelJson;
}


void ColourSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["colour"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _colour = std::make_shared<ColourData>(d);

      QPalette palette = _label->palette();
      palette.setColor(_label->backgroundRole(), _colour->colour());
      palette.setColor(_label->foregroundRole(), Qt::transparent);
      _label->setPalette(palette);
    }
  }
}


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

          QColor selection = QColorDialog::getColor();
          if( selection.isValid() )
          {

              QPalette palette = _label->palette();
              palette.setColor(_label->backgroundRole(), selection);
              palette.setColor(_label->foregroundRole(), Qt::transparent);
              _label->setPalette(palette);

              _colour = std::make_shared<ColourData>(selection);

              emit dataUpdated(0);
          }

        return true;
      }
    }

  return false;
}


NodeDataType ColourSourceDataModel::dataType(PortType, PortIndex) const
{
  return ColourData().type();
}


std::shared_ptr<NodeData>ColourSourceDataModel::outData(PortIndex)
{
  return _colour;
}
