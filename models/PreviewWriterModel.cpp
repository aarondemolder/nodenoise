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

PreviewWriterModel::PreviewWriterModel() : _label(new QLabel("Input Heightmap in Port 1 \n Diffuse in Port 2"))
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
      result = 2;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}



std::shared_ptr<NodeData>PreviewWriterModel::outData(PortIndex)
{
  return _nodeData;
}


void PreviewWriterModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
{
  _nodeData = nodeData;

  if (_nodeData)
  {
      if (port == 0)
      {
          auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

          QString fileName = "previews/preview_height.pre";

          QImage imgNew;
          imgNew = d->pixmap().toImage();
          QImage preview = imgNew.scaled(1024, 1024,Qt::KeepAspectRatio);

          QImageWriter writerQ(fileName, "png");
          writerQ.write(preview);

          _label->setText("Input Heightmap in Port 1 \n Diffuse in Port 2 \n Preview Saved");


      }

      if (port == 1)
      {

          auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

          QString fileName = "previews/preview_diffuse.pre";

          QImage imgNew;
          imgNew = d->pixmap().toImage();
          QImage preview = imgNew.scaled(1024, 1024,Qt::KeepAspectRatio);

          QImageWriter writerQ(fileName, "png");
          writerQ.write(preview);

          _label->setText("Input Heightmap in Port 1 \n Diffuse in Port 2 \n Preview Saved");

      }

  }

}
