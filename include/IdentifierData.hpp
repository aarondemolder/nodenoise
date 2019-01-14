#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class IdentifierData : public NodeData
{
public:

  IdentifierData() {}

  IdentifierData(QString const &identifier) : _identifier(identifier) {}

  NodeDataType type() const override { return NodeDataType {"identifier", "ID"}; }

  QString identifier() const { return _identifier; }

private:

  QString _identifier;
};
