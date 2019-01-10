#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
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
