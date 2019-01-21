#include "LnBillowModel.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>

#include <QImage>
#include <QPixmap>
#include <QImageWriter>


LnBillowModel::LnBillowModel() : _label(new QLabel("Billow Noise Module"))
{
    defaultImgRenderer();
}



unsigned int LnBillowModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 6;
      break;

    case PortType::Out:
      result = 3;

    default:
      break;
  }

  return result;
}


bool LnBillowModel::eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    int w = _label->width();
    int h = _label->height();

    if (event->type() == QEvent::MouseButtonPress)
    {

      _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));

      emit dataUpdated(2);

      return true;
    }
  }

  return false;
}

void LnBillowModel::onPixmapEdited(QPixmap const &pixmap)
{
  Q_UNUSED(pixmap);

  _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));

  emit dataUpdated(2);

}

void LnBillowModel::setInData(std::shared_ptr<NodeData> data, int)
{
  auto freqData = std::dynamic_pointer_cast<FreqData>(data);
  auto lacData = std::dynamic_pointer_cast<LacData>(data);
  auto octaveData = std::dynamic_pointer_cast<OctaveData>(data);
  auto perData = std::dynamic_pointer_cast<PerData>(data);
  auto seedData = std::dynamic_pointer_cast<SeedData>(data);
  auto qualityData = std::dynamic_pointer_cast<QualityData>(data);

  if (freqData)
  {
    _myBillowModule.SetFrequency(freqData->number());
  }

  if (lacData)
  {
    _myBillowModule.SetLacunarity(lacData->number());
  }

  if (octaveData)
  {
    _myBillowModule.SetOctaveCount(octaveData->number());
  }

  if (perData)
  {
    _myBillowModule.SetPersistence(perData->number());
  }

  if (seedData)
  {
    _myBillowModule.SetSeed(seedData->number());
  }

  if (qualityData)
  {
    if (qualityData->number()==0)
    {
        _myBillowModule.SetNoiseQuality(noise::QUALITY_FAST);
    }
    if (qualityData->number()==1)
    {
        _myBillowModule.SetNoiseQuality(noise::QUALITY_STD);
    }
    if (qualityData->number()==2)
    {
        _myBillowModule.SetNoiseQuality(noise::QUALITY_BEST);
    }
  }

  ///image preview processing

  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;

  heightMapBuilder.SetSourceModule (_myBillowModule);
  heightMapBuilder.SetDestNoiseMap (heightMap);
  heightMapBuilder.SetDestSize (256, 256);
  heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
  heightMapBuilder.Build ();

  utils::RendererImage renderer;
  utils::Image image;
  renderer.SetSourceNoiseMap (heightMap);
  renderer.SetDestImage (image);

  renderer.Render ();

  QImage imageOut(256, 256, QImage::Format_RGB32);
  QRgb value;

  for(int x=0; x < image.GetWidth(); x++)
      {
          for(int y=0; y < image.GetHeight(); y++)
          {
                  utils::Color c = image.GetValue(x,y);
                  value = qRgb(c.red, c.green, c.blue);
                  imageOut.setPixel(x, y, value);
          }
      }

  QTransform myTransform;
  myTransform.rotate(180);
  myTransform.scale(-1,1);
  imageOut = imageOut.transformed(myTransform);

  _pixmap = QPixmap::fromImage(imageOut);
  _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));


  emit dataUpdated(0);
  emit dataUpdated(1);
  emit dataUpdated(2);

}

void LnBillowModel::defaultImgRenderer()
{

    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;

    heightMapBuilder.SetSourceModule (_myBillowModule);
    heightMapBuilder.SetDestNoiseMap (heightMap);
    heightMapBuilder.SetDestSize (256, 256);
    heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
    heightMapBuilder.Build ();

    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);

    renderer.Render ();

    QImage imageOut(256, 256, QImage::Format_RGB32);
    QRgb value;

    for(int x=0; x < image.GetWidth(); x++)
        {
            for(int y=0; y < image.GetHeight(); y++)
            {
                    utils::Color c = image.GetValue(x,y);
                    value = qRgb(c.red, c.green, c.blue);
                    imageOut.setPixel(x, y, value);
            }
        }

    QTransform myTransform;
    myTransform.rotate(180);
    myTransform.scale(-1,1);
    imageOut = imageOut.transformed(myTransform);

    _pixmap = QPixmap::fromImage(imageOut);
    _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));
}
