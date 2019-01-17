#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
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
