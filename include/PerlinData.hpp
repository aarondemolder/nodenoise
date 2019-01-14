#ifndef PERLINDATA_H
#define PERLINDATA_H

#include <nodes/NodeDataModel>

#include <noise/noise.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class PerlinData : public NodeData
{
public:

  PerlinData() {}

  PerlinData(noise::module::Perlin const &myModule) : _myModule(myModule) {}

  NodeDataType type() const override { return NodeDataType {"perlin", "Terrain"}; }

  noise::module::Perlin myModule() const {return _myModule;}


private:

  noise::module::Perlin _myModule;


};

#endif // TERRAINDATA_H
