#pragma once

#include <QtGui/QPixmap>

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class PreviewData : public NodeData
{
public:

  PreviewData() {}

  PreviewData(QPixmap const &previewHeight, QPixmap const &previewDiffuse) : _previewHeight(previewHeight), _previewDiffuse(previewDiffuse) {}

  NodeDataType type() const override { return {"preview", "Preview"}; }

  QPixmap previewHeight() const { return _previewHeight; }

  QPixmap previewDiffuse() const { return _previewDiffuse; }

private:

  QPixmap _previewHeight;

  QPixmap _previewDiffuse;

};
