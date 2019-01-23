#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe the Resolution selection counter value used by the heightmap generator
class ResolutionData : public NodeData
{
public:

  ResolutionData() : _number(1){}

  ResolutionData(int const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"resolution","Resolution"};}

  int number() const { return _number; }

  QString numberAsText() const { return QString::number(_number); }

private:

  int _number;
};
