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
    _view3d->show();

    //_view3d->setParent();


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

//bool View3DModel::eventFilter(QObject *object, QEvent *event)
//{

//    if (object== _view3d)
//    {
//        if (event->type() == QEvent::MouseButtonPress)
//        {
//            _view3d->update();
//            event->accept();
//            this->embeddedWidget()->update();

//            std::cout<<"do we even get here?\n";
//            return true;
//        }
//    }



////    if (object == _label)
////    {
////      int w = _label->width();
////      int h = _label->height();

////      if (event->type() == QEvent::MouseButtonPress)
////      {

////        auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
////        if (d)
////        {

////            QString fileName = QFileDialog::getSaveFileName(nullptr,tr("Save Image"),QDir::homePath()+"/untitled.png",tr("Image File (*.png)"));

////            QImage newImg (256, 256, QImage::Format_RGB32);
////            newImg = d->pixmap().toImage();

////            QImageWriter writerQ(fileName, "png");
////            writerQ.write(newImg);

////            std::cout<<"QimageWritten\n";
////        }

////        return true;
////      }
////    }

//  return false;
//}


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

//  _nodeData = nodeData;

//  if (_nodeData)
//  {
//    auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

//    int w = _label->width();
//    int h = _label->height();

//    _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));

//    _view3d->update();

//  }
//  else
//  {
//    _label->setPixmap(QPixmap());
//  }

}
