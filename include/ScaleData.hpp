#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe Scale Values used in Scale Bias node - removed from build due to instability, might fix later
class ScaleData : public NodeData
{
public:

  ScaleData() : _scale(0.0){}

  ScaleData(double const scale) : _scale(scale){}

  NodeDataType type() const override {return NodeDataType {"scale","Scale"};}

  double scale() const { return _scale; }

private:

  double _scale;


};
