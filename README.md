# WaveShareDisplay
WaveShare 2.9" display for Judah's music box

Started from [Waveshare](https://github.com/waveshare/e-Paper)

TODO
* Use boost::di fork to wire together pieces
* Clear window to all white initially
* Set currently playing as default screen at startup
* Only send update to display if there are changes
* Make widget class and move over screen_XXX which are just examples
* Make LMS default play only locally
DONE * Fix string widget XY not taking into account all mirror and all rotate properly
DONE * Update README [markdown](https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf)
DONE * Get [drogon](https://drogon.docsforge.com/master/getting-started/#a-very-simple-example) built
DONE  * build and install JsonCPP
DONE  * build and install brotli
DONE  * build and install drogon with [deps](https://medium.com/@contact_80086/installing-drogon-ddb5d9949b75)
* Compare drogon app vs boost::asio::beast
  * Or what about belle octobanan
* Partial update of a windowed area
* Image of wave
  * [Floyd-Steinberg Dither](https://en.wikipedia.org/wiki/Floyd–Steinberg_dithering)
* Cube rotated and perspective [1](https://github.com/muralivnv/small-cpp-matrix-library/blob/master/matrix.h) [2](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix) [3](http://math.hws.edu/graphicsbook/source/glut/cubes-with-vertex-arrays.c)
* Dragon Curve fractal
DONE * Build web app (with drogon)
DONE  * Get LMS currently playing
  * Set LMS volume - to remove sbpd need
  * Get LMS volume - to remove sbpd need
  * Read rotary encoder and button - to remove sbpd need
  * Add picture to display
  * Display robot teeth
  * Add monkey [SVG](https://github.com/sammycage/lunasvg)
* Get dockcross builds setup
* Get Qemu running for RPi Zero
* [Improved e-ink update](https://www.instructables.com/Waveshare-EPaper-and-a-RaspberryPi/)
* WaveShare Links
   * [Dither](https://www.waveshare.com/wiki/E-Paper_Floyd-Steinberg)
   * [Products](https://www.waveshare.com/product/displays/e-paper/epaper-2/2.9inch-e-paper-module.htm)
   