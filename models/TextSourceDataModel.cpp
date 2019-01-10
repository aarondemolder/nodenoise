#include "TextSourceDataModel.hpp"

TextSourceDataModel::TextSourceDataModel() : _lineEdit(new QTextEdit("Notes..."))
{
//  connect(_lineEdit, &QTextEdit,this, &TextSourceDataModel::onTextEdited);
  _lineEdit->resize(200, 100);

}


unsigned int
TextSourceDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}


void TextSourceDataModel::onTextEdited(QString const &string)
{
  //Q_UNUSED(string);

  //emit dataUpdated(0);
}



NodeDataType TextSourceDataModel::dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>TextSourceDataModel::outData(PortIndex)
{
    //
    //return std::make_shared<TextData>(_lineEdit->text());
}
