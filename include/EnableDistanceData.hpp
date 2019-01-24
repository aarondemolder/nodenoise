#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe gradient type selection values used in Image Renderer node
class EnableDistanceData : public NodeData
{
public:

  EnableDistanceData() : _number(1){}

  EnableDistanceData(int const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"enabledistance","Distance Enabled"};}

  int number() const { return _number; }

  QString numberAsText() const { return QString::number(_number); }

private:

  int _number;
};
