#ifndef TERRAINDATA_H
#define TERRAINDATA_H

#include <nodes/NodeDataModel>

#include <noise/noise.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

//Class used to describe the various Terrain data types used by the heightmap generator
class TerrainData : public NodeData
{
public:

  TerrainData() {}

  TerrainData(noise::module::Perlin const &myPerlinModule) : _myPerlinModule(myPerlinModule) {}

  TerrainData(noise::module::RidgedMulti const &myRidgeModule) : _myRidgeModule(myRidgeModule) {}

  TerrainData(noise::module::Billow const &myBillowModule) : _myBillowModule(myBillowModule) {}

  TerrainData(noise::module::ScaleBias const &myScaleModule) : _myScaleModule(myScaleModule) {}

  TerrainData(noise::module::Voronoi const &myVoronoiModule) : _myVoronoiModule(myVoronoiModule) {}

  NodeDataType type() const override { return NodeDataType {"terrain", "Terrain"}; }

  noise::module::Perlin myPerlinModule() const {return _myPerlinModule;}

  noise::module::RidgedMulti myRidgeModule() const {return _myRidgeModule;}

  noise::module::Billow myBillowModule() const {return _myBillowModule;}

  noise::module::ScaleBias myScaleModule() const {return _myScaleModule;}

  noise::module::Voronoi myVoronoiModule() const {return _myVoronoiModule;}

private:

  noise::module::Perlin _myPerlinModule;

  noise::module::RidgedMulti _myRidgeModule;

  noise::module::Billow _myBillowModule;

  noise::module::ScaleBias _myScaleModule;

  noise::module::Voronoi _myVoronoiModule;

};

#endif // TERRAINDATA_H
