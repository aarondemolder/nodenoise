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

//This node accepts two image connections and saves them as '.pre' files into the preview folder
//These files are two 1024*1024 .png images in disguise, one heightmap and one diffuse
//NNPRV can then pick these files up, and generate a 3D preview
PreviewWriterModel::PreviewWriterModel() : _label(new QLabel("Input Heightmap in Port 1 \n Diffuse in Port 2 \n\n For best results, set resolution to at least \n 1024x1024!"))
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
      //here we do something different
      //where we have multiple inputs of the same type we can specify what port we want to copy the data from
      //of course in this case, we've told the user to plug the connection into the right ports
      //if the user gets it wrong, the terrain generation in the 3D previewer will be incorrect

      if (port == 0)
      {
          auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

          QString fileName = "previews/preview_height.pre";

          //create a new image, copy the input image data, and then scale the input to 1024*1024
          //only issue is that if the terrain generated is 256*256, it looks shit when it goes into the previewer
          QImage imgNew;
          imgNew = d->pixmap().toImage();
          QImage preview = imgNew.scaled(1024, 1024,Qt::KeepAspectRatio);

          QImageWriter writerQ(fileName, "png");
          writerQ.write(preview);

          //update label to let user know preview was saved
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
