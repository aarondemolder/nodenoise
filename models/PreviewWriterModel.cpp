#include "PreviewWriterModel.hpp"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>

#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"

#include <QImage>
#include <QPixmap>
#include <QImageWriter>
#include <QFileDialog>

PreviewWriterModel::PreviewWriterModel() : _label(new QLabel("Save Preview"))
{
  _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

  QFont f = _label->font();
  f.setBold(true);
  f.setItalic(true);

  _label->setFont(f);

  _label->setFixedSize(200, 200);

  _label->installEventFilter(this);
}

unsigned int PreviewWriterModel::nPorts(PortType portType) const
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


bool PreviewWriterModel::eventFilter(QObject *object, QEvent *event)
{


    if (object == _label)
    {

      if (event->type() == QEvent::MouseButtonPress)
      {

        auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
        if (d)
        {

            QString fileName = QFileDialog::getSaveFileName(nullptr,tr("Save Image"),QDir::homePath()+"/untitled.pre",tr("Preview File (*.pre)"));

            QImage imgNew;
            imgNew = d->pixmap().toImage();
            QImage preview = imgNew.scaled(1024, 1024,Qt::KeepAspectRatio);

            QImageWriter writerQ(fileName, "png");
            writerQ.write(preview);

            std::cout<<"QimageWritten\n";
        }

        return true;
      }
    }

  return false;
}


NodeDataType PreviewWriterModel::dataType(PortType, PortIndex) const
{
  return PixmapData().type();
}


std::shared_ptr<NodeData>PreviewWriterModel::outData(PortIndex)
{
  return _nodeData;
}


void PreviewWriterModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
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
