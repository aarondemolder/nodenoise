#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class SeedData : public NodeData
{
public:

  SeedData() : _number(0){}

  SeedData(int const number) : _number(number){}

  NodeDataType type() const override {return NodeDataType {"seed","Seed"};}

  int number() const { return _number; }

  QString numberAsText() const { return QString::number(_number); }

private:

  int _number;
};
