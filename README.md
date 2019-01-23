# nodenoise

A node based terrain generator using Qt, [Paceholder's Nodeeditor](https://github.com/paceholder/nodeeditor), and [libNoise](http://libnoise.sourceforge.net/index.html).

### Features

* Perlin, Billow & RidgedMulti noise generators with value setting nodes
* Heightmap Generation with resolution & bound setting nodes
* Image Rendering with automatic gradient generation - brightness, contrast & colour setting nodes
* Image Exporter (for use as displacement maps), Image viewer and Image Importer
* Preview Link node to send heightmaps to [NNPRV](https://github.com/aarondemolder/NNPRV) to preview heightmaps in 3D, and export OBJ files
* Ability to save and load node graphs in .flow files (json format)

### Known Issues

* Changing bounds or resolution values after heightmap generation doesn't affect result until the 'Terrain' input data is refreshed

![nodenoise graph editor](https://i.imgur.com/OIOE8md.jpg)

### NNPRV

Use [NNPRV](https://github.com/aarondemolder/NNPRV) to preview terrain as your generate your heightmaps.

![nodenoise editor and NNPRV](https://i.imgur.com/Kzemjit.jpg)
