#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe colour data used in Image Renderer node
class ColourData : public NodeData
{
public:

  ColourData() : _colour(255,255,255,255){}

  ColourData(QColor const colour) : _colour(colour){}

  NodeDataType type() const override {return NodeDataType {"colour","Colour"};}

  QColor colour() const { return _colour; }


private:

  QColor _colour;
};
