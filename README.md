# VectorTileRenderer

## Licence

This project is public and MIT-licensed.  
Forking and cloning are welcome.  
However, this repository does not accept external pull requests.  
Please use Issues for bug reports.

## Purpose

This project is an implementation of MapBox vector tile renderer. It's written
in C++23 in Visual Studio, but it should be quite portable to other platforms.

It supports MapBox Function syntax and the majority of Expression operations
relating to 2D tiles.

I've tested it with MVT mapping from ESRI (Basemap service), Ordnance Survey
(Open Zoomstack) and OpenFreeMap (https://openfreemap.org/).

## Features

- Support for loading vector tiles from from web servers or local MBTILE files.
- Support for MapBox glyphs and sprites.
- Flexible rendering output via abstract RenderTarget interface. Current
implementations are a raster renderer (using Direct2D) and a SVG renderer
(geometry only at this stage).
-Basic support for importing and rendering GeoJSON.

## Code Structure

`Core` contains the RenderTarget interface and a Direct2D and SVG implementation.
There are also platform-agnostic utility classes like Color, Bitmap, Geometry
and Logger.

`Formats` contains implementations of the MVT and GeoJSON formats.

`Geo` has classes for LatLong and a wrapper for PROJ to handle coordinate
transformations.

`IO` is concerned with loading data from a web server or from a file.

`Unicode` contains functions for converting between UTF-8 and UTF-32 and
for performing upper/lowercase conversions.

In addition there are a few simple test dialogs for testing the various
components of the project.

The `Unit Tests` project contains unit tests for the various components of the project.

## Credits

JSON for Modern C++ for JSON parsing (https://github.com/nlohmann/json)<br>
stb_image.h for loading bitmap images (https://github.com/nothings/stb)<br>
SQLite for reading MBTiles databases<br>
curl for downloading files from http servers<br>
zlib for decompressing downloaded files<br>
protobuf for decoding PBF-encoded data<br>

## Notes

I use AI clients for research and reference, but the project contains very
little AI-generated code (mostly Direct2D boilerplate for setup and saving
the image).

protoc installed with 'winget install protoc'

`protoc --cpp_out=. vector_tile.proto`

vcpkg installed via:

https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-msbuild?pivots=shell-cmd

vcpkg is used to install the following dependencies:

curl
zlib
protobuf
proj


To set up a temporary web server for serving data files:

```shell
python -m http.server 8000
```
