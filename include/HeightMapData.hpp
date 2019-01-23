#ifndef HEIGHTMAPDATA_H
#define HEIGHTMAPDATA_H

#include <nodes/NodeDataModel>

#include <noise/noise.h>
#include <noiseutils.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

//Class to describe all our heightmap data, which is used by the Image Renderer node
class HeightMapData : public NodeData
{
public:

  HeightMapData() {}

  HeightMapData(utils::NoiseMapBuilderPlane const &heightMapBuilder, utils::NoiseMap const &heightMap, int const &resolution) : _heightMapBuilder(heightMapBuilder), _heightMap(heightMap), _resolution(resolution) {}

  NodeDataType type() const override { return NodeDataType {"heightmap", "HeightMap"}; }

  utils::NoiseMapBuilderPlane heightMapBuilder() const {return _heightMapBuilder;}

  utils::NoiseMap heightMap() const {return _heightMap;}

  int resolution() const {return _resolution;}


private:


  utils::NoiseMapBuilderPlane _heightMapBuilder;

  utils::NoiseMap _heightMap;

  int _resolution;


};

#endif // TERRAINDATA_H
