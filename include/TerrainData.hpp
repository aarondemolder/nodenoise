#ifndef TERRAINDATA_H
#define TERRAINDATA_H

#include <nodes/NodeDataModel>

#include <noise/noise.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class TerrainData : public NodeData
{
public:

  TerrainData() {}

  TerrainData(QString const &text) : _text(text) {}

  NodeDataType type() const override { return NodeDataType {"terrain", "Terrain"}; }

  QString text() const { return _text; }

  //double number() const { return _number; }



private:

  QString _text;
};

#endif // TERRAINDATA_H
