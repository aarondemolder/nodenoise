#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

//General template class for text data
class TextData : public NodeData
{
public:

  TextData() {}

  TextData(QString const &text) : _text(text) {}

  NodeDataType type() const override { return NodeDataType {"text", "Text"}; }

  QString text() const { return _text; }

private:

  QString _text;
};
