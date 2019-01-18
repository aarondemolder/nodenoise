#include "LnScaleBiasModel.hpp"

#include "LnPerlinModel.hpp"

//#include "DecimalData.hpp"
#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>


LnScaleBiasModel::LnScaleBiasModel() : _label(new QLabel("Scale Bias"))
{

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);
    _label->installEventFilter(this);

    //prevents crash in case no bounds are set
    //_heightMapBuilder.SetBounds(6.0,10.0,1.0,5.0);

}


unsigned int LnScaleBiasModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 4;
      break;

    case PortType::Out:
      result = 2;

    default:
      break;
  }

  return result;
}


bool LnScaleBiasModel::eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    int w = _label->width();
    int h = _label->height();

//    if (event->type() == QEvent::Resize)
//    {
//      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
//      if (d)
//      {
//        _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
//      }
//    }
  }

  return false;
}

void LnScaleBiasModel::onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  //std::cout<<"FreqOut "<< _myPerlinModule->GetFrequency()<<"\n";

  emit dataUpdated(0);

}




void LnScaleBiasModel::setInData(std::shared_ptr<NodeData> data, int)
{
    auto identifierData = std::dynamic_pointer_cast<IdentifierData>(data);
    auto terrainData = std::dynamic_pointer_cast<TerrainData>(data);
    auto biasData = std::dynamic_pointer_cast<BiasData>(data);
    auto scaleData = std::dynamic_pointer_cast<ScaleData>(data);

    if (biasData)
    {
        _myScaleModule.SetBias (biasData->bias());

    }

    if (scaleData)
    {
        _myScaleModule.SetScale (scaleData->scale());
    }

    if (terrainData)
    {
        noise::module::Perlin perlinScaleBuilder = terrainData->myPerlinModule();

        _myScaleModule.SetSourceModule(0, perlinScaleBuilder);
//        _myScaleModule.SetScale (0.125);
//        _myScaleModule.SetBias (-0.75);

        utils::NoiseMap heightMap;
        utils::NoiseMapBuilderPlane heightMapBuilder;

        heightMapBuilder.SetSourceModule (_myScaleModule);
        heightMapBuilder.SetDestNoiseMap (heightMap);
        heightMapBuilder.SetDestSize (256, 256);
        heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
        heightMapBuilder.Build ();

        std::cout<<"built scale \n";

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

    }


}
