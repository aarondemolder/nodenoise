#include "LnHeightMapBuilder.hpp"

//#include "DecimalData.hpp"
#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>


LnHeightMapBuilder::LnHeightMapBuilder() : _label(new QLabel("LnHeightMapBuilder"))
{

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);
    _label->installEventFilter(this);


    //need to adjust this to be able to acces myModule from lnPerlinModel
    //myModule = std::make_shared<noise::module::Perlin>();

    //std::weak_ptr<noise::module::Perlin> myModuleImport = myModule;

    //we can call our module data functions like this
    //myModule->SetFrequency(2.0);

}


unsigned int LnHeightMapBuilder::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


bool LnHeightMapBuilder::eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    int w = _label->width();
    int h = _label->height();

//    if (event->type() == QEvent::Resize)
//    {
//      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
//      if (d)
//      {
//        _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
//      }
//    }
  }

  return false;
}

void LnHeightMapBuilder::onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  std::cout<<"FreqOut "<< myModule->GetFrequency()<<"\n";

  emit dataUpdated(0);

}

void LnHeightMapBuilder::setInData(std::shared_ptr<NodeData> data, int)
{
  auto terrainData = std::dynamic_pointer_cast<TerrainData>(data);

  if (terrainData)
  {
    //myModule->SetFrequency(freqData->number());
    //sets number input as label
    //_label->setText(freqData->numberAsText());
    std::cout<<"Terrain Data Present "<< myModule->GetFrequency()<<"\n";
  }



  //_label->adjustSize();
}




std::shared_ptr<NodeData>LnHeightMapBuilder::outData(PortIndex)
{
    //return NULL;
    return std::make_shared<TerrainData>();
}
