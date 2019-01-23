#include "ColourSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "ColourData.hpp"

#include "noise/noise.h"

//This node sets our colour values for the image renderer
//Create colour selection node with large QLabel
ColourSourceDataModel::ColourSourceDataModel(): _label(new QLabel("Click to select"))
{

    //formatting
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    _label->setAutoFillBackground(true);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);

    //allow us to trigger events when clicked
    _label->installEventFilter(this);

}

//colour value saving
QJsonObject ColourSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  //Should probably fix colour saving
  //if (_colour) modelJson["colour"] = QColor::name(_colour);

  return modelJson;
}

//colour value restoring
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

//configure ports
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

//event filter for clicks on the label
bool ColourSourceDataModel::eventFilter(QObject *object, QEvent *event)
{
    if (object == _label)
    {

      if (event->type() == QEvent::MouseButtonPress)
      {

          //open colour selection dialog
          QColor selection = QColorDialog::getColor();
          if( selection.isValid() )
          {

              //set background colour of label to be colour selection
              QPalette palette = _label->palette();
              palette.setColor(_label->backgroundRole(), selection);
              palette.setColor(_label->foregroundRole(), Qt::transparent);
              _label->setPalette(palette);

              //set colour value for node
              _colour = std::make_shared<ColourData>(selection);

              emit dataUpdated(0);
          }

        return true;
      }
    }

  return false;
}

//configure data output type
NodeDataType ColourSourceDataModel::dataType(PortType, PortIndex) const
{
  return ColourData().type();
}

//node data return
std::shared_ptr<NodeData>ColourSourceDataModel::outData(PortIndex)
{
  return _colour;
}
