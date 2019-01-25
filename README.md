# nodenoise

A node based terrain generator using Qt, [Paceholder's Nodeeditor](https://github.com/paceholder/nodeeditor), and [libnoise](http://libnoise.sourceforge.net/index.html).

### Features

* Perlin, Billow, RidgedMulti & Voronoi coherent noise generators with value setting nodes
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
* Heightmap clipping indicator

![nodenoise graph editor](https://i.imgur.com/OIOE8md.jpg)

### NNPRV

Use [NNPRV](https://github.com/aarondemolder/NNPRV) to preview terrain as your generate your heightmaps.

![nodenoise editor and NNPRV](https://i.imgur.com/Kzemjit.jpg)


### Video

[![video preview](https://i.imgur.com/Dimdb2M.png)](https://www.youtube.com/watch?v=8fXhktoyAAU)

### Setup
To setup nodenoise & nnprv to work with each other, just make sure you clone into the same directory: (this includes the [tests](https://github.com/aarondemolder/nodenoise_tests) )
![directory structure](https://i.imgur.com/6pfZ0bh.png)

1. Open nodenoise
2. Right click in the graph to open the node menu (you can search by typing!)
3. Connect your nodes together and output terrains!

A file demonstrating a simple graph is provided in flows/perlin_demo.flow
You can load this with the menu bar.

To create a terrain, you'll want:

1. A noise generator (Perlin, Billow, RidgedMulti, Voronoi)
	You can alter the values in these generators
2. A heightmap generator
	You can alter the resolution and generator bounds
3. Two Image Renderers, one for a heightmap and one for a diffuse
	You can alter brightness, contrast and light colour, as well as add an automatic gradient
4. An Image Writer or Preview Link
	Export high resolution textures for use as displacement maps in a renderer of your choice or preview your generation result in NNPRV, from here you can adjust your scale and export as OBJ

That's it!

### Trouble Building?

Link to a [handy fork of libnoise that uses cmake instead of static makefiles by qknight.](https://github.com/qknight/libnoise)
