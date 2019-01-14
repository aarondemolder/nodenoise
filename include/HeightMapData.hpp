#ifndef HEIGHTMAPDATA_H
#define HEIGHTMAPDATA_H

#include <nodes/NodeDataModel>

#include <noise/noise.h>
#include <noiseutils.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class HeightMapData : public NodeData
{
public:

  HeightMapData() {}

  HeightMapData(utils::NoiseMapBuilderPlane const &heightMapBuilder) : _heightMapBuilder(heightMapBuilder) {}

  NodeDataType type() const override { return NodeDataType {"heightmap", "HeightMap"}; }

  utils::NoiseMapBuilderPlane heightMapBuilder() const {return _heightMapBuilder;}


private:


  utils::NoiseMapBuilderPlane _heightMapBuilder;


};

#endif // TERRAINDATA_H
