#include "LnHeightMapBuilder.hpp"

#include "LnPerlinModel.hpp"

#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>
#include <noiseutils.h>

//This node takes data from a generator and builds a heightmap
LnHeightMapBuilder::LnHeightMapBuilder() : _label(new QLabel("LnHeightMapBuilder"))
{
    //formatting
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);

    //prevents crash in case no bounds are set
    _heightMapBuilder.SetBounds(6.0,10.0,1.0,5.0);

    //prevents crash if heightmap is plugged into image renderer without a generator
    noise::module::Perlin perlinBuilder;
    _heightMapBuilder.SetSourceModule (perlinBuilder);
    _heightMapBuilder.SetDestNoiseMap (_heightMap);
    _heightMapBuilder.SetDestSize (256, 256);
    _heightMapBuilder.Build ();

}



unsigned int LnHeightMapBuilder::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 4;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


void LnHeightMapBuilder::setInData(std::shared_ptr<NodeData> data, int)
{
    auto identifierData = std::dynamic_pointer_cast<IdentifierData>(data);
    auto terrainData = std::dynamic_pointer_cast<TerrainData>(data);
    auto resolutionData = std::dynamic_pointer_cast<ResolutionData>(data);
    auto boundsData = std::dynamic_pointer_cast<BoundsData>(data);

    if (boundsData)
    {
        //checks if bound entires are valid to prevent libnoise throwing exceptions and exiting
        if(boundsData->numberXL() >= boundsData->numberXU() || boundsData->numberZL() >= boundsData->numberZU())
        {
            _label->setText("INVALID BOUNDS");
            _boundSet = 0;
        }
        else
        {
            _heightMapBuilder.SetBounds(boundsData->numberXL(),boundsData->numberXU(),boundsData->numberZL(),boundsData->numberZU());
            _label->setText("Bounds Set");
            _boundSet = 1;
        }

    }

    if (identifierData)
    {
        //we require an 'ID' so we know what kind of generator has been input
        _idText = identifierData->identifier();
        _idSet = 1;
        _label->setText("ID Set");
    }

    if (resolutionData)
    {
      //taking the index value from a combobox - we set a resolution
      _resSet = resolutionData->number();

      if (_resSet == 0)
      {
          _resSize = 256;
          _resolution = _resSize;
          _label->setText("256 Resolution Set");

          //we used to emit data here but it causes the image renderer to hang when resolution is decreased after an initial render
          //emit dataUpdated(0);
      }

      if (_resSet == 1)
      {
          _resSize = 512;
          _resolution = _resSize;
          _label->setText("512 Resolution Set");
          //emit dataUpdated(0);
      }

      if (_resSet == 2)
      {
          _resSize = 1024;
          _resolution = _resSize;
          _label->setText("1024 Resolution Set");
          //emit dataUpdated(0);
      }

      if (_resSet == 3)
      {
          _resSize = 2048;
          _resolution = _resSize;
          _label->setText("2048 Resolution Set");
          //emit dataUpdated(0);
      }

      if (_resSet == 4)
      {
          _resSize = 4096;
          _resolution = _resSize;
          _label->setText("4096 Resolution Set");
          //emit dataUpdated(0);
      }
    }

    if (terrainData)
    {
        //check for terrain ID
        if (_idSet == 0)
        {
            _label->setText("ID NOT SET");
        }
        //if ID OK
        if (_idSet == 1)
        {
            //compare the ID string passed with our known generator types
            if ((QString::compare(_idText, "perlin")) == 0) // should return 0 if true
            {
                //virtual void in Build() needs this - we're making a copy of the data
                noise::module::Perlin perlinBuilder = terrainData->myPerlinModule();

                //build our heightmap
                _heightMapBuilder.SetSourceModule (perlinBuilder);
                _heightMapBuilder.SetDestNoiseMap (_heightMap);
                _heightMapBuilder.SetDestSize (_resSize, _resSize);
                _heightMapBuilder.Build ();

                _label->setText("Perlin HeightMap Done");

                //emit heightmap data
                emit dataUpdated(0);
            }

            if ((QString::compare(_idText, "billow")) == 0)
            {
                noise::module::Billow billowBuilder = terrainData->myBillowModule();

                _heightMapBuilder.SetSourceModule (billowBuilder);
                _heightMapBuilder.SetDestNoiseMap (_heightMap);
                _heightMapBuilder.SetDestSize (_resSize, _resSize);
                _heightMapBuilder.Build ();

                _label->setText("Billow HeightMap Done");

                emit dataUpdated(0);
            }

            if ((QString::compare(_idText, "ridge")) == 0)
            {
                noise::module::RidgedMulti ridgeBuilder = terrainData->myRidgeModule();

                _heightMapBuilder.SetSourceModule (ridgeBuilder);
                _heightMapBuilder.SetDestNoiseMap (_heightMap);
                _heightMapBuilder.SetDestSize (_resSize, _resSize);
                _heightMapBuilder.Build ();

                _label->setText("Ridge HeightMap Done");

                emit dataUpdated(0);
            }

            //scale was removed but it's okay to leave this here
            if ((QString::compare(_idText, "scale")) == 0)
            {
                noise::module::ScaleBias scaleBuilder = terrainData->myScaleModule();

                _heightMapBuilder.SetSourceModule (scaleBuilder);
                _heightMapBuilder.SetDestNoiseMap (_heightMap);
                _heightMapBuilder.SetDestSize (_resSize, _resSize);
                _heightMapBuilder.Build ();

                _label->setText("Scale HeightMap Done");

                emit dataUpdated(0);
            }
        }
    }
}

//return all the data needed for the image renderer node
std::shared_ptr<NodeData>LnHeightMapBuilder::outData(PortIndex)
{
    return std::make_shared<HeightMapData>(_heightMapBuilder,_heightMap,_resolution);
}
