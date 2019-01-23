# nodenoise

A node based terrain generator using Qt, [Paceholder's Nodeeditor](https://github.com/paceholder/nodeeditor), and [libnoise](http://libnoise.sourceforge.net/index.html).

### Features

* Perlin, Billow & RidgedMulti coherent noise generators with value setting nodes
* Heightmap Generation with resolution & bound setting nodes
* Image Rendering with automatic gradient generation - brightness, contrast & colour setting nodes
* Image Exporter (for use as displacement maps), Image viewer and Image Importer
* Preview Link node to send heightmaps to [NNPRV](https://github.com/aarondemolder/NNPRV) to preview heightmaps in 3D, and export OBJ files
* Ability to save and load node graphs in .flow files (json format)

![coherent obj exports](https://i.imgur.com/YQU32K9.png)

### Known Issues

* Changing bounds or resolution values after heightmap generation doesn't affect result until the 'Terrain' input data is refreshed - temp workaround is by clicking generator image

### Future Features

* libnoise Scale Bias implementation
* libnoise Selection & Combiner nodes
* User input paint tools for raising/digging terrain - though for now this can be done on the OBJ in 3D DCC of choice by scalaing a soft selection.
* Multi-threaded noise generation by dividing chunks set by the bounds
* Image combiner nodes such as Add, Multiply, Divide etc

![nodenoise graph editor](https://i.imgur.com/OIOE8md.jpg)

### NNPRV

Use [NNPRV](https://github.com/aarondemolder/NNPRV) to preview terrain as your generate your heightmaps.

![nodenoise editor and NNPRV](https://i.imgur.com/Kzemjit.jpg)

Link to a [handy fork of libnoise that uses cmake instead of static makefiles by qknight.](https://github.com/qknight/libnoise)

A demo .flow file is provided in flows/perlin_demo.flow

Video:

[![video preview](https://img.youtube.com/vi/8fXhktoyAAU/maxresdefault.jpg)](https://www.youtube.com/watch?v=8fXhktoyAAU)
