#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe the Quality selection counter data used by the noise generators
class QualityData : public NodeData
{
public:

  QualityData() : _number(1){}

  QualityData(int const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"quality","Quality"};}

  int number() const { return _number; }

  QString numberAsText() const { return QString::number(_number); }

private:

  int _number;
};
