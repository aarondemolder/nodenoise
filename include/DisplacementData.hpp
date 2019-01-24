#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe frequency data values used in noise generator nodes
class DisplacementData : public NodeData
{
public:

  DisplacementData() : _number(0.0){}

  DisplacementData(double const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"disp","Displacement"};}

  double number() const { return _number; }

  QString numberAsText() const { return QString::number(_number, 'f'); }

private:

  double _number;
};
