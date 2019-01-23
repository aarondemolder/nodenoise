#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class used to describe the light brightness values used by the Image Renderer node
class LightBrightnessData : public NodeData
{
public:

  LightBrightnessData() : _number(2.0){}

  LightBrightnessData(double const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"lightbrightness","LightBrightness"};}

  double number() const { return _number; }

  QString numberAsText() const { return QString::number(_number, 'f'); }

private:

  double _number;
};
