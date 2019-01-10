#ifndef PERLINDATA_H
#define PERLINDATA_H

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class PerlinData : public NodeData
{
public:

  PerlinData() {}

  PerlinData(QString const &text) : _text(text) {}

  NodeDataType type() const override { return NodeDataType {"terrain", "Terrain"}; }

  QString text() const { return _text; }

  //double number() const { return _number; }


private:

  QString _text;
};

#endif // PERLINDATA_H
