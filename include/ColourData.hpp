#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class ColourData : public NodeData
{
public:

  ColourData() : _colour(255.0,255.0,255.0,255.0){}

  ColourData(QColor const colour) : _colour(colour){}

  NodeDataType type() const override {return NodeDataType {"colour","Colour"};}

  QColor colour() const { return _colour; }


private:

  QColor _colour;
};
