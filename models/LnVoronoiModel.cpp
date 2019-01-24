#include "LnVoronoiModel.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>

#include <QImage>
#include <QPixmap>
#include <QImageWriter>

//This node generates perlin noise using default values or using user input value, it outputs an ID, heightmap data and an image
LnVoronoiModel::LnVoronoiModel() : _label(new QLabel("Voronoi Noise Module"))
{
    //click to regenerate fix
    _label->installEventFilter(this);
    defaultImgRenderer();
}



unsigned int LnVoronoiModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 4;
      break;

    case PortType::Out:
      result = 3;

    default:
      break;
  }

  return result;
}

//we emit heightmap data when the label is clicked
bool LnVoronoiModel::eventFilter(QObject *object, QEvent *event)
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

//emit image if image is updated
void LnVoronoiModel::onPixmapEdited(QPixmap const &pixmap)
{
  Q_UNUSED(pixmap);

  _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));

  emit dataUpdated(2);

}

//set generator values from user input
void LnVoronoiModel::setInData(std::shared_ptr<NodeData> data, int)
{
  auto freqData = std::dynamic_pointer_cast<FreqData>(data);
  auto seedData = std::dynamic_pointer_cast<SeedData>(data);
  auto enableDistanceData  = std::dynamic_pointer_cast<EnableDistanceData>(data);
  auto displacementData = std::dynamic_pointer_cast<DisplacementData>(data);


  if (freqData)
  {
    _myVoronoiModule.SetFrequency(freqData->number());
  }

  if (seedData)
  {
    _myVoronoiModule.SetSeed(seedData->number());
  }

  if (enableDistanceData)
  {
    _myVoronoiModule.EnableDistance(enableDistanceData->number());
  }

  if (displacementData)
  {
    _myVoronoiModule.SetDisplacement(displacementData->number());
  }

  //image preview processing
  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;

  heightMapBuilder.SetSourceModule (_myVoronoiModule);
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
void LnVoronoiModel::defaultImgRenderer()
{

    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;

    heightMapBuilder.SetSourceModule (_myVoronoiModule);
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
