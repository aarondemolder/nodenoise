#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class BiasData : public NodeData
{
public:

  BiasData() : _bias(0.0){}

  BiasData(double const bias) : _bias(bias){}

  NodeDataType type() const override {return NodeDataType {"bias","Bias"};}

  double bias() const { return _bias; }

private:

  double _bias;


};
