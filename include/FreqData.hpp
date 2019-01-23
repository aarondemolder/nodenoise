#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe frequency data values used in noise generator nodes
class FreqData : public NodeData
{
public:

  FreqData() : _number(0.0){}

  FreqData(double const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"freq","Frequency"};}

  double number() const { return _number; }

  QString numberAsText() const { return QString::number(_number, 'f'); }

private:

  double _number;
};
