//DEMONSTRATION

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

  NodeDataType type() const override { return NodeDataType {"perlin", "Perlin"}; }

  //NodeDataType type() const override { return NodeDataType {"text", "Test"}; }

  QString text() const { return _text; }



  //add our frequency and etc definitions here? we need different classes for the different datatypes?

 // double number() const { return _number; }


private:

  QString _text;
};

#endif // PERLINDATA_H
