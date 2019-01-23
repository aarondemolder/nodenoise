#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class used to describe Lacunarity data used by the noise generator nodes
class LacData : public NodeData
{
public:

  LacData() : _number(1.5){}

  LacData(double const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"lac","Lacunarity"};}

  double number() const { return _number; }

  QString numberAsText() const { return QString::number(_number, 'f'); }

private:

  double _number;
};
