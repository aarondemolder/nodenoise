#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe Bias Values used in Scale Bias node - removed from build due to instability, might fix later
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
