#include "LnPerlinModel.hpp"

//#include "DecimalData.hpp"
#include "PixmapData.hpp"

#include <QtCore/QEvent>

#include <noise/noise.h>


LnPerlinModel::LnPerlinModel() : _label(new QLabel("Perlin Noise Module"))
{
    //connect(_moduleNameEdit, &QLineEdit::textEdited,this, &LnPerlinModel::onTextEdited);

    //text bits
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);
    _label->setFont(f);
    _label->setFixedSize(200, 200);
    _label->installEventFilter(this);


    //make pointer for module
    myModule = std::make_shared<noise::module::Perlin>();
    //we can call our module data functions like this
    myModule->SetFrequency(2.0);

}


//std::shared_ptr <------ stores references to data with some implication of ownership (internally stores a reference count that is incremented/decremented as the amount of shared_ptrs related to that data increases - immediately destroyed when ref count is == 0)
//std::weak_ptr   <------ also stores reference to data - but only that created with shared_ptr - does not increment the ref count in any way and can only access it through using the .lock() function on the weak_ptr (which actually returns a shared_ptr so you can do weak.lock()->foo()) - throws exception if .lock() is called on weak_ptr which is pointed at nothing

// shared_ptr = implies some ownership
// weak_ptr   = interacts with data with no implied ownership in a safe manner




unsigned int LnPerlinModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 6;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


bool LnPerlinModel::eventFilter(QObject *object, QEvent *event)
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

void LnPerlinModel::onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  std::cout<<"FreqOut "<< myModule->GetFrequency()<<"\n";

  emit dataUpdated(0);

}

void LnPerlinModel::setInData(std::shared_ptr<NodeData> data, int)
{
  auto freqData = std::dynamic_pointer_cast<FreqData>(data);
  auto lacData = std::dynamic_pointer_cast<LacData>(data);
  auto octaveData = std::dynamic_pointer_cast<OctaveData>(data);
  auto perData = std::dynamic_pointer_cast<PerData>(data);
  auto seedData = std::dynamic_pointer_cast<SeedData>(data);
  auto qualityData = std::dynamic_pointer_cast<QualityData>(data);

  if (freqData)
  {
    myModule->SetFrequency(freqData->number());
    //sets number input as label
    //_label->setText(freqData->numberAsText());
    std::cout<<"FreqOut "<< myModule->GetFrequency()<<"\n";
  }

  if (lacData)
  {
    myModule->SetLacunarity(lacData->number());
    std::cout<<"LacOut "<< myModule->GetLacunarity()<<"\n";
  }

  if (octaveData)
  {
    myModule->SetOctaveCount(octaveData->number());
    std::cout<<"OctaveOut "<< myModule->GetOctaveCount()<<"\n";
  }

  if (perData)
  {
    myModule->SetPersistence(perData->number());
    std::cout<<"PerOut "<< myModule->GetPersistence()<<"\n";
  }

  if (seedData)
  {
    myModule->SetSeed(seedData->number());
    std::cout<<"SeedOut "<< myModule->GetSeed()<<"\n";
  }

  if (qualityData)
  {
    if (qualityData->number()==0)
    {
        myModule->SetNoiseQuality(noise::QUALITY_FAST);
        std::cout<<"QualityOut "<< myModule->GetNoiseQuality()<<"\n";
    }
    if (qualityData->number()==1)
    {
        myModule->SetNoiseQuality(noise::QUALITY_STD);
        std::cout<<"QualityOut "<< myModule->GetNoiseQuality()<<"\n";
    }
    if (qualityData->number()==2)
    {
        myModule->SetNoiseQuality(noise::QUALITY_BEST);
        std::cout<<"QualityOut "<< myModule->GetNoiseQuality()<<"\n";
    }
  }


  //_label->adjustSize();
}


//now defined in the header
//NodeDataType LnPerlinModel::dataType(PortType, PortIndex) const
//{
//  return PerlinData().type();
//}


std::shared_ptr<NodeData>LnPerlinModel::outData(PortIndex)
{
    //return NULL;
    //return std::make_shared<PerlinData>();
}
