#pragma once

#include <QtCore/QObject>
//#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
//#include <QtWidgets/QTextEdit>

#include "PerlinData.hpp"

#include "DecimalData.hpp"

#include "FreqData.hpp"
#include "LacData.hpp"
#include "OctaveData.hpp"
#include "PerData.hpp"
#include "SeedData.hpp"
#include "QualityData.hpp"

#include "PixmapData.hpp"

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <iostream>

#include <noise/noise.h>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;



/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class LnPerlinModel : public NodeDataModel
{
  Q_OBJECT

public:
  LnPerlinModel();

  std::shared_ptr<noise::module::Perlin> myModule;

  virtual
  ~LnPerlinModel() {}

public:

  QString caption() const override { return QString("Perlin Model"); }

  bool captionVisible() const override { return true; }

  static QString Name() { return QString("Perlin Noise Generator"); }

  QString name() const override { return LnPerlinModel::Name(); }

public:

  unsigned int nPorts(PortType portType) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData> data, int) override;

  QWidget *embeddedWidget() override { return _label; }

  bool resizable() const override { return true; }

public:

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override
  {
    switch (portType)
    {
      case PortType::In:
        switch (portIndex)
        {
            case 0:
                return FreqData().type();
            case 1:
                return LacData().type();
            case 2:
                return OctaveData().type();
            case 3:
                return PerData().type();
            case 4:
                return SeedData().type();
            case 5:
                return QualityData().type();
        }
        break;

    case PortType::Out:
      switch (portIndex)
      {
        case 0:
          return PerlinData().type();
        case 1://unused
          return PixmapData().type();
      }
      break;

    case PortType::None:
      break;

    }
    return NodeDataType();
  }

protected:

  bool eventFilter(QObject *object, QEvent *event) override;

private slots:

  void onTextEdited(QString const &string);


private:

  QLabel * _label;

  //QLineEdit * _moduleNameEdit;

  //QTextEdit * _lineEdit;

};
