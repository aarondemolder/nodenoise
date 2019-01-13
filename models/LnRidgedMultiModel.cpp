#include "LnRidgedMultiModel.hpp"

//#include "DecimalData.hpp"
#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>


#include <QImage>
#include <QPixmap>
#include <QImageWriter>


LnRidgedMultiModel::LnRidgedMultiModel() : _label(new QLabel("LnRidgedMultiModel Module"))
{
    //connect(_moduleNameEdit, &QLineEdit::textEdited,this, &LnPerlinModel::onTextEdited);

    //text bits
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(256, 256);
    _label->installEventFilter(this);

    //make pointer for module
    myModule = std::make_shared<noise::module::RidgedMulti>();

    defaultImgRenderer();
}


unsigned int LnRidgedMultiModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 6;
      break;

    case PortType::Out:
      result = 2;

    default:
      break;
  }

  return result;
}


bool LnRidgedMultiModel::eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    int w = _label->width();
    int h = _label->height();

    if (event->type() == QEvent::MouseButtonPress)
    {

      _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));

      emit dataUpdated(1);

      return true;
    }
    else if (event->type() == QEvent::Resize)
    {
      if (!_pixmap.isNull())
        _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));
    }
  }

  return false;
}

void LnRidgedMultiModel::onPixmapEdited(QPixmap const &pixmap)
{
  Q_UNUSED(pixmap);

  _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));
  std::cout<<"FreqOut "<< myModule->GetFrequency()<<"\n";

  emit dataUpdated(1);

}

void LnRidgedMultiModel::setInData(std::shared_ptr<NodeData> data, int)
{
  auto freqData = std::dynamic_pointer_cast<FreqData>(data);
  auto lacData = std::dynamic_pointer_cast<LacData>(data);
  auto octaveData = std::dynamic_pointer_cast<OctaveData>(data);
  auto perData = std::dynamic_pointer_cast<PerData>(data);
  auto seedData = std::dynamic_pointer_cast<SeedData>(data);
  auto qualityData = std::dynamic_pointer_cast<QualityData>(data);

  if (freqData)
  {
    myModule->SetFrequency(freqData->number());
    refmyModule.SetFrequency(freqData->number());
    //sets number input as label
    //_label->setText(freqData->numberAsText());
    //std::cout<<"FreqOut "<< myModule->GetFrequency()<<"\n";
  }

  if (lacData)
  {
    myModule->SetLacunarity(lacData->number());
    refmyModule.SetLacunarity(lacData->number());
    //std::cout<<"LacOut "<< myModule->GetLacunarity()<<"\n";
  }

  if (octaveData)
  {
    myModule->SetOctaveCount(octaveData->number());
    refmyModule.SetOctaveCount(octaveData->number());
    //std::cout<<"OctaveOut "<< myModule->GetOctaveCount()<<"\n";
  }

//  if (perData)
//  {
//    myModule->SetPersistence(perData->number());
//    refmyModule.SetPersistence(perData->number());
//    //std::cout<<"PerOut "<< myModule->GetPersistence()<<"\n";
//  }

  if (seedData)
  {
    myModule->SetSeed(seedData->number());
    refmyModule.SetSeed(seedData->number());
    //std::cout<<"SeedOut "<< myModule->GetSeed()<<"\n";
  }

  if (qualityData)
  {
    if (qualityData->number()==0)
    {
        myModule->SetNoiseQuality(noise::QUALITY_FAST);
        //std::cout<<"QualityOut "<< myModule->GetNoiseQuality()<<"\n";
    }
    if (qualityData->number()==1)
    {
        myModule->SetNoiseQuality(noise::QUALITY_STD);
        //std::cout<<"QualityOut "<< myModule->GetNoiseQuality()<<"\n";
    }
    if (qualityData->number()==2)
    {
        myModule->SetNoiseQuality(noise::QUALITY_BEST);
        //std::cout<<"QualityOut "<< myModule->GetNoiseQuality()<<"\n";
    }
  }

  ///image processing for Perlin noise

  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;

  heightMapBuilder.SetSourceModule (refmyModule);
  //heightMapBuilder.SetSourceModule (myModule);
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


  emit dataUpdated(1);
  //emit noiseChanged(myModule);

}

void LnRidgedMultiModel::defaultImgRenderer()
{

    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;

    heightMapBuilder.SetSourceModule (refmyModule);
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
