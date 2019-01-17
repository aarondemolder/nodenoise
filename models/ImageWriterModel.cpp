#include "ImageWriterModel.hpp"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>

#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"

#include <QImage>
#include <QPixmap>
#include <QImageWriter>
#include <QFileDialog>

ImageWriterModel::ImageWriterModel() : _label(new QLabel("Image Preview"))
{
  _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

  QFont f = _label->font();
  f.setBold(true);
  f.setItalic(true);

  _label->setFont(f);

  _label->setFixedSize(200, 200);

  _label->installEventFilter(this);
}

unsigned int ImageWriterModel::nPorts(PortType portType) const
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


bool ImageWriterModel::eventFilter(QObject *object, QEvent *event)
{


    if (object == _label)
    {
      int w = _label->width();
      int h = _label->height();

      if (event->type() == QEvent::MouseButtonPress)
      {

        auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
        if (d)
        {

            QString fileName = QFileDialog::getSaveFileName(nullptr,tr("Save Image"),QDir::homePath()+"/untitled.png",tr("Image File (*.png)"));

            QImage newImg (256, 256, QImage::Format_RGB32);
            newImg = d->pixmap().toImage();

            QImageWriter writerQ(fileName, "png");
            writerQ.write(newImg);

            std::cout<<"QimageWritten\n";
        }

        return true;
      }
    }

  return false;
}


NodeDataType ImageWriterModel::dataType(PortType, PortIndex) const
{
  return PixmapData().type();
}


std::shared_ptr<NodeData>ImageWriterModel::outData(PortIndex)
{
  return _nodeData;
}


void ImageWriterModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
  _nodeData = nodeData;

  if (_nodeData)
  {
    auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

    int w = _label->width();
    int h = _label->height();

    _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
  }
  else
  {
    _label->setPixmap(QPixmap());
  }

}
