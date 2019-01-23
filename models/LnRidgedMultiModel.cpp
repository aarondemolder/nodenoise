#include "LnRidgedMultiModel.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>

#include <QImage>
#include <QPixmap>
#include <QImageWriter>

//This node generates RidgedMulti noise using user inputs
LnRidgedMultiModel::LnRidgedMultiModel() : _label(new QLabel("RidgedMulti Noise Module"))
{
    //same click fix as other generators
    _label->installEventFilter(this);
    defaultImgRenderer();
}



unsigned int LnRidgedMultiModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 5;
      break;

    case PortType::Out:
      result = 3;

    default:
      break;
  }

  return result;
}

//click fix event
bool LnRidgedMultiModel::eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    if (event->type() == QEvent::MouseButtonPress)
    {
      emit dataUpdated(1);

      return true;
    }
  }

  return false;
}

//update image output if generation occurs
void LnRidgedMultiModel::onPixmapEdited(QPixmap const &pixmap)
{
  Q_UNUSED(pixmap);

  _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));

  emit dataUpdated(2);

}

//generates noise using user input
void LnRidgedMultiModel::setInData(std::shared_ptr<NodeData> data, int)
{
  auto freqData = std::dynamic_pointer_cast<FreqData>(data);
  auto lacData = std::dynamic_pointer_cast<LacData>(data);
  auto octaveData = std::dynamic_pointer_cast<OctaveData>(data);
  auto seedData = std::dynamic_pointer_cast<SeedData>(data);
  auto qualityData = std::dynamic_pointer_cast<QualityData>(data);

  if (freqData)
  {
    _myRidgeModule.SetFrequency(freqData->number());
  }

  if (lacData)
  {
    _myRidgeModule.SetLacunarity(lacData->number());
  }

  if (octaveData)
  {
    _myRidgeModule.SetOctaveCount(octaveData->number());
  }

  if (seedData)
  {
    _myRidgeModule.SetSeed(seedData->number());
  }

  if (qualityData)
  {
    if (qualityData->number()==0)
    {
        _myRidgeModule.SetNoiseQuality(noise::QUALITY_FAST);
    }
    if (qualityData->number()==1)
    {
        _myRidgeModule.SetNoiseQuality(noise::QUALITY_STD);
    }
    if (qualityData->number()==2)
    {
        _myRidgeModule.SetNoiseQuality(noise::QUALITY_BEST);
    }
  }

  //image preview processing
  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;

  heightMapBuilder.SetSourceModule (_myRidgeModule);
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

//ensures data exists to send to heightmap builder even if no input connections are made
void LnRidgedMultiModel::defaultImgRenderer()
{

    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;

    heightMapBuilder.SetSourceModule (_myRidgeModule);
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
