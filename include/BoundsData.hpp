#pragma once

#include <nodes/NodeDataModel>


using QtNodes::NodeDataType;
using QtNodes::NodeData;

//Class to describe Bounds coordinates values used in Heightmap generator node
class BoundsData : public NodeData
{
public:

  BoundsData() : _numberXL(0.0), _numberXU(0.0), _numberZL(0.0), _numberZU(0.0) {}

  BoundsData(double const numberXL, double const numberXU, double const numberZL, double const numberZU) : _numberXL(numberXL), _numberXU(numberXU), _numberZL(numberZL), _numberZU(numberZU){}


  NodeDataType type() const override {return NodeDataType {"bounds","Bounds"};}


  double numberXL() const { return _numberXL; }

  double numberXU() const { return _numberXU; }


  double numberZL() const { return _numberZL; }

  double numberZU() const { return _numberZU; }



private:

  double _numberXL;

  double _numberXU;


  double _numberZL;

  double _numberZU;




};
