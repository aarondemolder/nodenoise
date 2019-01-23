#include "TextSourceDataModel.hpp"

//This node provides a text box for notes around the graph editor, it's not connected to anything
//It also saves the notes!
TextSourceDataModel::TextSourceDataModel() : _lineEdit(new QTextEdit("Notes..."))
{
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

//text saving
QJsonObject TextSourceDataModel::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_lineEdit) modelJson["text"] = _lineEdit->toPlainText();

  return modelJson;
}

//text restoring
void TextSourceDataModel::restore(QJsonObject const &p)
{
  QJsonValue v = p["text"];

  if (!v.isUndefined())
  {
    QString text = v.toString();

    _lineEdit->setText(text);
  }
}

void TextSourceDataModel::onTextEdited()
{
  QString text = _lineEdit->toPlainText();

  emit dataUpdated(0);
}


NodeDataType TextSourceDataModel::dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>TextSourceDataModel::outData(PortIndex)
{
    //
}
