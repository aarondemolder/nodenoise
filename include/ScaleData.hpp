#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
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
