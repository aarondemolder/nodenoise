#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe gradient type selection values used in Image Renderer node
class AutoGradientData : public NodeData
{
public:

  AutoGradientData() : _number(1){}

  AutoGradientData(int const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"autogradient","AutoGradient"};}

  int number() const { return _number; }

  QString numberAsText() const { return QString::number(_number); }

private:

  int _number;
};
