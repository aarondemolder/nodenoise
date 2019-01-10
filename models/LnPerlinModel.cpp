#include "LnPerlinModel.hpp"

//#include "DecimalData.hpp"
#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>


#include <QImage>
#include <QPixmap>
#include <QImageWriter>


LnPerlinModel::LnPerlinModel() : _label(new QLabel("Perlin Noise Module"))
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
    myModule = std::make_shared<noise::module::Perlin>();

    defaultImgRenderer();
}


//std::shared_ptr <------ stores references to data with some implication of ownership (internally stores a reference count that is incremented/decremented as the amount of shared_ptrs related to that data increases - immediately destroyed when ref count is == 0)
//std::weak_ptr   <------ also stores reference to data - but only that created with shared_ptr - does not increment the ref count in any way and can only access it through using the .lock() function on the weak_ptr (which actually returns a shared_ptr so you can do weak.lock()->foo()) - throws exception if .lock() is called on weak_ptr which is pointed at nothing

// shared_ptr = implies some ownership
// weak_ptr   = interacts with data with no implied ownership in a safe manner




unsigned int LnPerlinModel::nPorts(PortType portType) const
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


bool LnPerlinModel::eventFilter(QObject *object, QEvent *event)
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

void LnPerlinModel::onPixmapEdited(QPixmap const &pixmap)
{
  Q_UNUSED(pixmap);

  _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));
  std::cout<<"FreqOut "<< myModule->GetFrequency()<<"\n";

  emit dataUpdated(1);

}

void LnPerlinModel::setInData(std::shared_ptr<NodeData> data, int)
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

  if (perData)
  {
    myModule->SetPersistence(perData->number());
    refmyModule.SetPersistence(perData->number());
    //std::cout<<"PerOut "<< myModule->GetPersistence()<<"\n";
  }

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
  heightMapBuilder.SetDestNoiseMap (heightMap);
  heightMapBuilder.SetDestSize (256, 256);
  heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
  heightMapBuilder.Build ();

  utils::RendererImage renderer;
  utils::Image image;
  renderer.SetSourceNoiseMap (heightMap);
  renderer.SetDestImage (image);

  renderer.Render ();

  ///this bit works for now, so we know the generation works
//  utils::WriterBMP writer;
//  writer.SetSourceImage (image);
//  writer.SetDestFilename ("outimage.bmp");
//  writer.WriteDestFile ();

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

///this part also works, so our Qimage has data
//  QImageWriter writerQ("outimage.png", "png");
//  writerQ.write(imageOut);

//  std::cout<<"QimageWritten\n";

  _pixmap = QPixmap::fromImage(imageOut);
  _label->setPixmap(_pixmap.scaled(256, 256, Qt::KeepAspectRatio));

  emit dataUpdated(1);

}

void LnPerlinModel::defaultImgRenderer()
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


///now defined in the header
//NodeDataType LnPerlinModel::dataType(PortType, PortIndex) const
//{
//  return PerlinData().type();
//}

//std::shared_ptr<NodeData>LnPerlinModel::outData(PortIndex)
//{
//    //return NULL;
//    return std::make_shared<TerrainData>();
//}
