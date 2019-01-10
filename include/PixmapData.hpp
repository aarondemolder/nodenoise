#pragma once

#include <QtGui/QPixmap>

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class PixmapData : public NodeData
{
public:

  PixmapData() {}

  PixmapData(QPixmap const &pixmap) : _pixmap(pixmap) {}

  NodeDataType type() const override { return {"pixmap", "Image"}; }

  QPixmap pixmap() const { return _pixmap; }

private:

  QPixmap _pixmap;

};
