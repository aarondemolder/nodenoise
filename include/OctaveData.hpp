#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class used to describe the Octave values used by the noise generators
class OctaveData : public NodeData
{
public:

  OctaveData() : _number(1){}

  OctaveData(int const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"octave","Octave"};}

  int number() const { return _number; }

  QString numberAsText() const { return QString::number(_number); }

private:

  int _number;
};
