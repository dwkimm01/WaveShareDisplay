# WaveShareDisplay
WaveShare 2.9" display for Judah's music box

TODO
* Add version history
* Use boost::di fork to wire together pieces
* Consider extracting widgets from screen_XXX which are just examples
* Set LMS volume - to remove sbpd need
* Get LMS volume - to display on eink
* Read rotary encoder and button - to remove sbpd need
* Add picture display functionality
* Fix Display robot teeth
* Make LMS default play only locally
* Partial update of a windowed area
* Image of wave
  * [Floyd-Steinberg Dither](https://en.wikipedia.org/wiki/Floyd–Steinberg_dithering)
* Cube rotated and perspective [1](https://github.com/muralivnv/small-cpp-matrix-library/blob/master/matrix.h) [2](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix) [3](http://math.hws.edu/graphicsbook/source/glut/cubes-with-vertex-arrays.c)
* Dragon Curve fractal
* Get dockcross builds setup
* Get Qemu running for RPi Zero
* [Improved e-ink update](https://www.instructables.com/Waveshare-EPaper-and-a-RaspberryPi/)

DONE
* Make host_url and player_name command line configurable
* Clear window to all white initially
* Set currently playing as default screen at startup
* Only send update to display if there are changes
* Make widget class 
* Fix string widget XY not taking into account all mirror and all rotate properly
* Update README [markdown](https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf)
* Get [drogon](https://drogon.docsforge.com/master/getting-started/#a-very-simple-example) built
* build and install JsonCPP
* build and install brotli (drogon dep)
* build and install drogon with [deps](https://medium.com/@contact_80086/installing-drogon-ddb5d9949b75)
* Build web app (with drogon)
* Get LMS currently playing
* Display robot teeth
* Add monkey [SVG](https://github.com/sammycage/lunasvg) (did bmp monkey instead)
* Could compare drogon app vs boost::asio::beast - but this seems to work well enough
  * Or what about belle octobanan  

Links
* WaveShare
   * [Dither](https://www.waveshare.com/wiki/E-Paper_Floyd-Steinberg)
   * [Products](https://www.waveshare.com/product/displays/e-paper/epaper-2/2.9inch-e-paper-module.htm)
   * [Waveshare](https://github.com/waveshare/e-Paper) is a starting point for eink code
   