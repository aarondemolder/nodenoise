#include "View3DModel.hpp"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <nodes/Node>
#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QImageWriter>
#include <QVBoxLayout>
#include <QWidget>
#include <QGraphicsSceneHoverEvent>


View3DModel::View3DModel(): _view3d(new GLWidget())
{
    //displays another openglwindow seperate
    //_view3d->show();

    _view3d->installEventFilter(this);

}


unsigned int View3DModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}

bool View3DModel::eventFilter(QObject *object, QEvent *event)
{

    if (object== _view3d)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {


            std::cout<<"click?\n";
            return true;
        }
    }
  return false;
}


NodeDataType View3DModel::dataType(PortType, PortIndex) const
{
  return PixmapData().type();
}


std::shared_ptr<NodeData>View3DModel::outData(PortIndex)
{
  return _nodeData;
}


void View3DModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{


}
