#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class used to describe the Persistence values used by the noise generators
class PerData : public NodeData
{
public:

  PerData() : _number(0.0){}

  PerData(double const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"per","Persistence"};}

  double number() const { return _number; }

  QString numberAsText() const { return QString::number(_number, 'f'); }

private:

  double _number;
};
