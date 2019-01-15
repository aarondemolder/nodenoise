#include "LnHeightMapBuilder.hpp"

#include "LnPerlinModel.hpp"

//#include "DecimalData.hpp"
#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>


LnHeightMapBuilder::LnHeightMapBuilder() : _label(new QLabel("LnHeightMapBuilder"))
{

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);
    _label->installEventFilter(this);

}


unsigned int LnHeightMapBuilder::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 3;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


bool LnHeightMapBuilder::eventFilter(QObject *object, QEvent *event)
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

void LnHeightMapBuilder::onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  //std::cout<<"FreqOut "<< _myPerlinModule->GetFrequency()<<"\n";

  emit dataUpdated(0);

}





void LnHeightMapBuilder::setInData(std::shared_ptr<NodeData> data, int)
{
    auto identifierData = std::dynamic_pointer_cast<IdentifierData>(data);
    auto terrainData = std::dynamic_pointer_cast<TerrainData>(data);
    auto resolutionData = std::dynamic_pointer_cast<ResolutionData>(data);

    if (identifierData)
    {
        //std::cout<<"identifier "<< identifierData->identifier().toUtf8().constData()<<"\n";
        _idText = identifierData->identifier();
        _idSet = 1;
    }

    if (resolutionData)
    {
      _resSet = resolutionData->number();
      std::cout<<"resSet "<< _resSet<<"\n";

      if (_resSet == 0)
      {
          _resSize = 256;
      }

      if (_resSet == 1)
      {
          _resSize = 512;
      }

      if (_resSet == 2)
      {
          _resSize = 1024;
      }

      if (_resSet == 3)
      {
          _resSize = 2048;
      }

      if (_resSet == 4)
      {
          _resSize = 4096;
      }
    }

    if (terrainData)
    {
        if (_idSet == 0)
        {
            std::cout<<"ID NOT SET \n";
        }

        if (_idSet == 1)
        {
            if ((QString::compare(_idText, "perlin")) == 0) // should return 0 if true
            {
                std::cout<<"PERLIN CONFIRMED \n";
                std::cout<<"FreqPerlinOut "<< terrainData->myPerlinModule().GetFrequency()<<"\n";

                //virtual void in Build() needs this
                noise::module::Perlin perlinBuilder = terrainData->myPerlinModule();

                utils::NoiseMap heightMap;

                _heightMapBuilder.SetSourceModule (perlinBuilder);
                _heightMapBuilder.SetDestNoiseMap (heightMap);
                _heightMapBuilder.SetDestSize (_resSize, _resSize);
                _heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
                _heightMapBuilder.Build ();

                std::cout<<"built \n";

                emit dataUpdated(0);

            }

            if ((QString::compare(_idText, "ridge")) == 0)
            {
                std::cout<<"RIDGE CONFIRMED \n";
                std::cout<<"FreqRidgeOut "<< terrainData->myRidgeModule().GetFrequency()<<"\n";

                //virtual void in Build() needs this
                noise::module::Billow billowBuilder = terrainData->myBillowModule();

                utils::NoiseMap heightMap;

                _heightMapBuilder.SetSourceModule (billowBuilder);
                _heightMapBuilder.SetDestNoiseMap (heightMap);
                _heightMapBuilder.SetDestSize (256, 256);
                _heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
                _heightMapBuilder.Build ();

                std::cout<<"built \n";

                emit dataUpdated(0);
            }

            if ((QString::compare(_idText, "billow")) == 0)
            {
                std::cout<<"BILLOW CONFIRMED \n";
                std::cout<<"FreqBillowOut "<< terrainData->myBillowModule().GetFrequency()<<"\n";

                //virtual void in Build() needs this
                noise::module::RidgedMulti ridgeBuilder = terrainData->myRidgeModule();

                utils::NoiseMap heightMap;

                _heightMapBuilder.SetSourceModule (ridgeBuilder);
                _heightMapBuilder.SetDestNoiseMap (heightMap);
                _heightMapBuilder.SetDestSize (256, 256);
                _heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
                _heightMapBuilder.Build ();

                std::cout<<"built \n";

                emit dataUpdated(0);
            }
        }
    }
}


std::shared_ptr<NodeData>LnHeightMapBuilder::outData(PortIndex)
{
    return std::make_shared<HeightMapData>(_heightMapBuilder);
}
