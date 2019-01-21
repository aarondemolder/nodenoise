#include "ImageRenderModel.hpp"

#include "LnPerlinModel.hpp"

//#include "DecimalData.hpp"
#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>


ImageRenderModel::ImageRenderModel() : _label(new QLabel("ImageRender Model"))
{

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);
    _label->installEventFilter(this);


}


unsigned int ImageRenderModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 5;
      break;

    case PortType::Out:
      result = 2;

    default:
      break;
  }

  return result;
}


bool ImageRenderModel::eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    int w = _label->width();
    int h = _label->height();

    if (event->type() == QEvent::Resize)
    {
        _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));
    }
  }

  return false;
}

void ImageRenderModel::onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  //std::cout<<"FreqOut "<< _myPerlinModule->GetFrequency()<<"\n";

  emit dataUpdated(0);

}




void ImageRenderModel::setInData(std::shared_ptr<NodeData> data, int)
{
    auto heightmapData = std::dynamic_pointer_cast<HeightMapData>(data);
    auto lightbrightnessData = std::dynamic_pointer_cast<LightBrightnessData>(data);
    auto lightcontrastData = std::dynamic_pointer_cast<LightContrastData>(data);
    auto autogradientData = std::dynamic_pointer_cast<AutoGradientData>(data);
    auto colourData = std::dynamic_pointer_cast<ColourData>(data);

    if(colourData)
    {
        _colour = colourData->colour();
        noise::utils::Color lnColour = utils::Color (  _colour.red(), _colour.green(), _colour.blue(), _colour.alpha());

        renderer.EnableLight();
        renderer.SetLightColor(lnColour);
    }

    if (lightbrightnessData)
    {
        renderer.EnableLight();
        renderer.SetLightBrightness(lightbrightnessData->number());
    }

    if (lightcontrastData)
    {
        renderer.EnableLight();
        renderer.SetLightContrast(lightcontrastData->number());
    }

    if(heightmapData)
    {
        _heightMap = heightmapData->heightMap();
        _resolution = heightmapData->resolution();
    }


    int w = _label->width();
    int h = _label->height();

    //renderer.BuildTerrainGradient();

    if (autogradientData)
    {
        if (autogradientData->number()==0)
        {
            renderer.BuildGrayscaleGradient();
        }
        if (autogradientData->number()==1)
        {
            renderer.BuildTerrainGradient();
        }
    }

    renderer.SetSourceNoiseMap (_heightMap);
    renderer.SetDestImage (image);
    renderer.Render ();

    //image to pixmap

    QImage imageOut(_resolution, _resolution, QImage::Format_RGB32);
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
    _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));

    emit dataUpdated(0);

}


std::shared_ptr<NodeData>ImageRenderModel::outData(PortIndex)
{
    return std::make_shared<PixmapData>(_pixmap);
}
