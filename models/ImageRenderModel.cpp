#include "ImageRenderModel.hpp"

#include "LnPerlinModel.hpp"

#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>

//This node renders libnoise heightmap data into images that can be exported
//Large QLabel node
ImageRenderModel::ImageRenderModel() : _label(new QLabel("ImageRender Model"))
{
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);

}

//port config
unsigned int ImageRenderModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 5;
      break;

    case PortType::Out:
      result = 1.;

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


//When we have a connection made to the node inputs, runs related if statements
void ImageRenderModel::setInData(std::shared_ptr<NodeData> data, int)
{
    auto heightmapData = std::dynamic_pointer_cast<HeightMapData>(data);
    auto lightbrightnessData = std::dynamic_pointer_cast<LightBrightnessData>(data);
    auto lightcontrastData = std::dynamic_pointer_cast<LightContrastData>(data);
    auto autogradientData = std::dynamic_pointer_cast<AutoGradientData>(data);
    auto colourData = std::dynamic_pointer_cast<ColourData>(data);

    if(colourData)
    {
        //get the reported colour value and set our renderer's light colour
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
        //copy heightmap & resolution data and flag it
        _resolution = heightmapData->resolution();
        _heightMap = heightmapData->heightMap();

        _heightMapSet = 1;
    }


    if (autogradientData)
    {
        //specify if we're using greyscale or colour default gradients
        if (autogradientData->number()==0)
        {
            renderer.BuildGrayscaleGradient();
        }
        if (autogradientData->number()==1)
        {
            renderer.BuildTerrainGradient();
        }
    }

    //would be nice to include this to allow the user to build their own custom gradients
    //renderer.BuildTerrainGradient();

    int w = _label->width();
    int h = _label->height();

    //if heightmap build flag is set then...
    if (_heightMapSet == 1)
    {

        //render heightmap
        renderer.SetSourceNoiseMap (_heightMap);
        renderer.SetDestImage (image);
        renderer.Render ();

        if(_resolution < heightmapData->resolution())
        {
          _resolution = heightmapData->resolution();
        }

        QImage imageOut(_resolution, _resolution, QImage::Format_RGB32);
        QRgb value;

        //get values from renderer and convert to QImage
        for(int x=0; x < image.GetWidth(); x++)
            {
                for(int y=0; y < image.GetHeight(); y++)
                {
                        utils::Color c = image.GetValue(x,y);
                        value = qRgb(c.red, c.green, c.blue);
                        imageOut.setPixel(x, y, value);
                }
            }

        //transform image to match libNoise's own image writer
        QTransform myTransform;
        myTransform.rotate(180);
        myTransform.scale(-1,1);
        imageOut = imageOut.transformed(myTransform);

        //convert to pixmap, set pixmap as label, and emit
        _pixmap = QPixmap::fromImage(imageOut);
        _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));

        emit dataUpdated(0);
        _heightMapSet = 0;
    }
    else
    {
        _label->setText("HeightMap Required");
    }

}

//config port data type
std::shared_ptr<NodeData>ImageRenderModel::outData(PortIndex)
{
    return std::make_shared<PixmapData>(_pixmap);
}
